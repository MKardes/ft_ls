#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

static char    listAddBack(t_list **list, const char *parentPath, const char *name, long *maxSize, long *total)
{
	struct stat (status) = {};
	char		*filePath = getPath(parentPath, name);
	if (lstat(filePath, &status) < 0)
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", filePath, strerror(errno));
		free(filePath);
		return '\0';
	}
	t_list *(tmp) = NULL; 
	t_file *(obj) = NULL;
	obj = (t_file *)malloc(sizeof(t_file));
	ft_bzero(obj, sizeof(t_file));
	obj->name = ft_strdup(name);
	obj->time = status.STAT_TIME.tv_sec;
	obj->ntime = status.STAT_TIME.tv_nsec;
	obj->acm = get_acm(status.st_mode);
	if (total && *total != -1){
		if (obj->acm[0] == 'l')
		{
			char link_path[1024];
			int  byte = readlink(filePath, link_path, 1024);
			link_path[byte] = '\0'; 
			char *tmp = obj->name;
			obj->name = ft_strjoin(tmp, " -> ");
			free(tmp);
			tmp = obj->name;
			obj->name = ft_strjoin(tmp, link_path);
			free(tmp);
		}
		obj->nlink = status.st_nlink;
		if (maxSize[0] < obj->nlink)
			maxSize[0] = obj->nlink;
		obj->pw_name = ft_strdup(getpwuid(status.st_uid)->pw_name);
		if (maxSize[1] < (long)ft_strlen(obj->pw_name))
			maxSize[1] = (long)ft_strlen(obj->pw_name);
		obj->gr_name = ft_strdup(getgrgid(status.st_gid)->gr_name);
		if (maxSize[2] < (long)ft_strlen(obj->gr_name))
			maxSize[2] = (long)ft_strlen(obj->gr_name);
		obj->size = status.st_size;
		if (maxSize[3] < obj->size)
			maxSize[3] = obj->size;
		*total += status.st_blocks;
	}
	tmp = ft_lstnew(obj);
	ft_lstadd_back(list, tmp);
	free(filePath);
	return (obj->acm[0]);
}

int ls(const char *modes, const t_dir *directory, int flag, int *nl_flag)
{
	long    maxSize[4] = {0,0,0,0};
	long    total = (modes[1] == 'l') ? 0 : -1;
	t_list* list = NULL;
	t_list* recDirs = NULL;
	char*   path = NULL;
	char    type;

	if (!directory)
		return(-1);
	if (!directory->dir){
		printFile(directory->path, modes[1] == 'l');
		return (0);
	}
	if (flag == 1)
		path = directory->path;
	dirPoint dir = readdir(directory->dir);
	while(dir)
	{
		if (dir->d_name[0] == '.' && modes[0] != 'a') {
			dir = readdir(directory->dir);
			continue ;
		}
		type = listAddBack(&list, directory->path, dir->d_name, maxSize, &total);
		if (modes[2] == 'R' && type == 'd' && ft_strncmp(dir->d_name, "..", 3) != 0 && ft_strncmp(dir->d_name, ".", 2) != 0) // type == f
			listAddBack(&recDirs, directory->path, dir->d_name, NULL, NULL);
		dir = readdir(directory->dir);
	}
	sortList(&list, modes, 0);
	printList(list, maxSize, total, path, nl_flag);
	ft_lstclear(&list, &delLList);

	sortList(&recDirs, modes, 0);
	t_list* recRoot = recDirs;
	while(recDirs){
		char		*filePath = getPath(directory->path, ((t_file *)(recDirs->content))->name);
		t_dir* dir = openDir(filePath);
		if (dir){
			ls(modes, dir, ((flag == 2) ? 1 : flag), nl_flag);
			del_dirs(dir);
		}
		recDirs = recDirs->next;
	}
	ft_lstclear(&recRoot, &delLList);
	return(0);
}
