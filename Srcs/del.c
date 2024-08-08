#include "ft_ls.h"

void	del_dirs(void *e)
{
	if(!e)
		return;
	t_dir *(arg) = (t_dir *)e;
	closedir(arg->dir);
	free(arg->path);
	// if (arg->date)
	// 	free(arg->date);
	free(arg);
}

void    delLList(void *e)
{
	t_file* arg = (t_file*)e;
	free(arg->name);
	// free(arg->date);
	if (arg->acm)
		free(arg->acm);
	if (arg->pw_name)
		free(arg->pw_name);
	if (arg->gr_name)
		free(arg->gr_name);
	free(arg);
}