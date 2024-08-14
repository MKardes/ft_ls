#include "libft.h"
#include "ft_ls.h"
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// t_list: 
//  {
//      t_dir *content
//      void *next
//  }
static int	add_dir(t_list **list, char *path, int *dir_cnt)
{
	struct stat (status) = {};
	t_list *(tmp) = NULL;
	t_dir *(new_dir) = NULL;
	if (lstat(path, &status) < 0)
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	new_dir = (t_dir *)malloc(sizeof(t_dir));
	if (!new_dir)
		return (-1);
	if (S_ISDIR(status.st_mode)){
		DIR *(dir) = opendir(path);
		if (!dir) {
			ft_printf_fd(2, "ft_ls: %s: %s\n", path, strerror(errno));
			return(-1);
		}
		new_dir->dir = dir;
		(*dir_cnt)++;
	}
	else
		new_dir->dir = NULL;
	new_dir->path = ft_strdup(path);
	new_dir->time = status.st_mtim.tv_sec;
	new_dir->ntime = status.st_mtim.tv_nsec;
	tmp = ft_lstnew(new_dir);
	ft_lstadd_back(list, tmp);
	return (1);
}

static t_list	*dirs(char **dirs, int *dir_cnt)
{
	t_list *(res) = NULL;
	int (i) = 0;
	while (dirs[i])
	{
		if (add_dir(&res, dirs[i], dir_cnt) < 0)
			return (NULL);
		i++;
	}
	i = -1;
	while (dirs[++i])
		free(dirs[i]);
	free(dirs);
	return (res);
}

// checks if a directory or file present in arguments
t_list	*get_files(int ac, char *argv[], int file_cnt, int *dir_cnt)
{
	int (i) = 0;
	int (dirI) = 0;
	int	(flag) = 0;
	char **(dir_strs) = NULL;
	if (file_cnt == 0)
	{
		dir_strs = (char **)malloc(sizeof(char *) * 2);
		if (!dir_strs)
			return (NULL);
		dir_strs[0] = ft_strdup(".");
		dir_strs[1] = NULL;
	}
	else {
		dir_strs = (char **)malloc(sizeof(char *) * (file_cnt + 1));
		if (!dir_strs)
			return (NULL);
		dir_strs[file_cnt] = NULL;
		while (++i < ac) {
			if (flag || argv[i][0] != '-' || (argv[i][0] == '-' && ft_strlen(argv[i]) == 0)){
				flag = 1;
				dir_strs[dirI++] = ft_strdup(argv[i]);
			}
		}
	}
	return (dirs(dir_strs, dir_cnt));
}

static void	fill_modes(char *opt, char *modes)
{
	int	j;

	j = 0;
	while (opt[++j])
	{
		if (opt[j] == 'a')
			modes[0] = 'a';
		else if (opt[j] == 'l')
			modes[1] = 'l';
		else if (opt[j] == 'R')
			modes[2] = 'R';
		else if (opt[j] == 'r')
			modes[3] = 'r';
		else if (opt[j] == 't')
			modes[4] = 't';
		else
		{
			ft_printf_fd(2, "ls: illegal option -- '%c'\n", opt[j]);
			ft_printf_fd(2, "usage: ls [-%s] [file ...]\n", MODES);
			exit(2);
		}
	}
}

// gets mode flags and returns number of mode arguments
int	get_flags(int ac, char *argv[], char *modes)
{
	int (i) = 0;
	int (cnt) = 0;
	ft_memset(modes, '-', MAX_MODES);
	while (++i < ac)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
		{
			cnt++;
			fill_modes(argv[i], modes);
		}
		else
			break;
	}
	return (cnt);
}
