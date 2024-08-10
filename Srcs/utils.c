#include "ft_ls.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

char* getPath(const char* dir_path, const char*  dir_name)
{
	char*		path = NULL;
	if (!dir_path || !dir_name)
		return NULL;
	if (ft_strcmp(dir_path, "") == 0){
		return ft_strdup(dir_name);
	}
	char* tmp = ft_strjoin(dir_path, "/");
	path = ft_strjoin(tmp, dir_name);
	free(tmp);
	return path;
}

static int cmp_by_time(void *first, void *second, char type){
	int cmp_result = 0;
	if (type == 0){
		
		cmp_result = ((t_file *)(second))->time - ((t_file *)(first))->time;
			if (cmp_result == 0) {
				cmp_result = ((t_file *)(second))->ntime - ((t_file *)(first))->ntime;
			}
	}
	else {
		cmp_result = ((t_dir *)(second))->time - ((t_dir *)(first))->time;
			if (cmp_result == 0){
				cmp_result = ((t_dir *)(second))->ntime - ((t_dir *)(first))->ntime;
			}
	}
	return cmp_result;
}

static void sort(t_list *list, char sortType, char type) {
	t_list *(tmp) = NULL;
	while (list->next)
	{
		tmp = list->next;
    	while (tmp)
		{
			void *first = (list->content);
			void *second = (tmp->content);
			int	cmp_result = 0;
			if (sortType == 't')
				cmp_result = cmp_by_time(first, second, type);
			else if (sortType == 'n')
				cmp_result = ft_strcmp(((char **)(first))[0], ((char **)(second))[0]); // compares names
			if (cmp_result > 0){
				list->content = second;
				tmp->content = first;
			}
			tmp = tmp->next;
		}
		list = list->next;
	}
}

static t_list *reverse(t_list *list){
	t_list *(head) = list;
	t_list *(tmp) = NULL;
	t_list *(tmp2) = NULL;
	while(head != NULL) {
		tmp2 = head->next;
		head->next = tmp;
		tmp = head;
		head = tmp2;
	}
	return(tmp);
}

void sortList(t_list **list, const char *modes, char type)
{
	t_list *(tmp) = NULL;
	if (!list || !(*list) || ft_lstsize(*list) == 1)
		return;
	sort(*list, 'n', type);
	if (modes[4] == 't')
		sort(*list, 't', type);
	if (modes[3] == 'r')
		*list = reverse(*list);
}

t_dir* openDir(char* dir_path)
{
	DIR*   		open = NULL;
	t_dir* 		dir = NULL;
	struct stat	info;

	if (!dir_path)
		return NULL;
	// to see if the file has loop because of the symbolic links
	if (lstat(dir_path, &info) == 0)
		open = opendir(dir_path);
	if (!open)
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", dir_path, strerror(errno));
		return (NULL);
	}
	else
	{
		dir = (t_dir *)malloc(sizeof(t_dir));
		if (!dir)
			return (NULL);
		dir->dir = open;
		dir->path = dir_path;
		// dir->date = NULL;
	}
	return (dir);
}
