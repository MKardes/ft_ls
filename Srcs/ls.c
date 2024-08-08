#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

static char    listAddBack(t_list **list, const char *parentPath, const char *name, long *maxSize, long *total)
{
	struct stat (status) = {};
	char		*filePath = getPath(parentPath, name);
	if (lstat(filePath, &status) < 0)
	{
		ft_printf("Status info couldn't be taken!\n");
		free(filePath);
		return '\0';
	}
	t_list *(tmp) = NULL; 
	t_listF *(obj) = NULL;
	obj = (t_listF *)malloc(sizeof(t_listF));
	ft_bzero(obj, sizeof(t_listF));
	obj->name = ft_strdup(name);
	obj->date = ft_substr(ctime(&status.st_mtime), 4, 13);
	obj->date[ft_strlen(obj->date) - 1] = '\0';
	obj->acm = get_acm(status.st_mode);
	// obj->date = ft_substr(ctime(&status.st_mtim.tv_sec), 4, 13);
	if (*total != -1){
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
		// *total += status.st_blocks / 2;
	}
	tmp = ft_lstnew(obj);
	ft_lstadd_back(list, tmp);
	free(filePath);
	return (obj->acm[0]);
}

void    delLList(void *e)
{
	t_listF* arg = (t_listF*)e;
	free(arg->date);
	free(arg->name);
	free(arg->acm);
	if (arg->pw_name)
		free(arg->pw_name);
	if (arg->gr_name)
		free(arg->gr_name);
	free(arg);
}

void    delList(void *e)
{
	free(e);
}

t_dir* openDir(char* dir_path)
{
	DIR*   		open = NULL;
	t_dir* 		dir = NULL;
	struct stat	info;

	// to see if the file has loop because of the symbolic links
	if (lstat(dir_path, &info) == 0)
		open = opendir(dir_path);
	if (!open)
	{
		char error[100];
		if (errno == EACCES)
			ft_strlcpy(error, "ft_ls: cannot open directory '", 28);
		else
			ft_strlcpy(error, "ft_ls: cannot access '", 23);
		ft_strlcat(error, dir_path, ft_strlen(dir_path) + ft_strlen(error) + 1);
		ft_strlcat(error, "'", ft_strlen(error) + 2);
		free(dir_path);
		perror(error);
		return (NULL);
	}
	else
	{
		dir = (t_dir *)malloc(sizeof(t_dir));
		if (!dir)
			return (NULL);
		dir->dir = open;
		dir->path = dir_path;
	}
	return (dir);
}

/**
 * @param list the list contains files
 * @param flag variable to realise the type 
 * of the list to get the string using as 
 * the name of a the file 
 * 0 - t_list is list of t_list*
 * 1 - t_list is list of t_dir*
 * 2 - t_list is list of char*
 * @param isReverse variable to realise if
 * the r flag is given to make the ls command
 * lists reverse 
 */
void sortList(t_list *list, int flag, int isReverse){
	t_list *(tmp) = NULL;
	if (!list || ft_lstsize(list) == 1)
		return;
	while (list->next)
	{
		tmp = list->next;
    	while (tmp)
		{
			void *first = (list->content);
			char *second = (tmp->content);
			int	cmp_result = 0;
			
			if (flag == 0) {
                cmp_result = ft_strcmp(((t_listF*)first)->name, ((t_listF*)second)->name);
            } else if (flag == 1) {
                cmp_result = ft_strcmp(((t_dir*)first)->path, ((t_dir*)second)->path);
            } else if (flag == 2) {
                cmp_result = ft_strcmp((char *)first, (char *)second);
            }

            if (isReverse) {
                cmp_result = -cmp_result;
            }
			if (cmp_result > 0){
				list->content = second;
				tmp->content = first;
			}
			tmp = tmp->next;
		}
		list = list->next;
	}
}

int ls(const char *modes, t_dir *directory, bool flag)
{
	long    maxSize[4] = {0,0,0,0};
	long    total = (modes[1] == 'l') ? 0 : -1;
	t_list* list = NULL;
	t_list* recDirs = NULL;
	char*   path = NULL;
	char    type;

	if (!directory)
		return(2);
	if (flag)
		path = directory->path;
	dirPoint dir = readdir(directory->dir);
	while(dir)
	{
		// size için hepsinin size ını bilip ona göre listele(hizalamak için)
		if (dir->d_name[0] == '.' && modes[0] != 'a')
		{
			dir = readdir(directory->dir);
			continue ;
		}
		type = listAddBack(&list, directory->path, dir->d_name, maxSize, &total);
		if (modes[2] == 'R' && type == 'd' && ft_strncmp(dir->d_name, "..", 3) != 0 && ft_strncmp(dir->d_name, ".", 2) != 0) // type == f
		{
			char *path = getPath(directory->path, dir->d_name);
			// t_dir* recDir = openDir(directory->path, dir->d_name);
			if(path != NULL){
				t_list* entity = ft_lstnew(path);
				ft_lstadd_back(&recDirs, entity);
			}
		}
		dir = readdir(directory->dir);
	}
	sortList(list, 0, modes[3] == 'r');
	printList(list, maxSize, total, path);
	ft_lstclear(&list, &delLList);

	t_list* recRoot = recDirs;
	sortList(recDirs, 2, modes[3] == 'r');
	while(recDirs){
		t_dir* dir = openDir(recDirs->content);
		if (dir){
			ls(modes, dir, flag);
			recDirs = recDirs->next;
			del_dirs(dir);
		}
		else {
			free(recDirs->content);
		}
	}
	ft_lstclear(&recRoot, &del_list);
	return(0);
}
