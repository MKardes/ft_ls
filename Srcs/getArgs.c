#include "libft.h"
#include "ft_ls.h"
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

// t_list: 
//  {
//      t_dir *content
//      void *next
//  }
static int	add_dir(t_list **list, DIR *dir, char *path)
{
	char	error[100];

	t_list *(tmp) = NULL;
	t_dir *(new_dir) = NULL;
	if (!dir)
	{
		if (errno == EACCES)
			ft_strlcpy(error, "ft_ls: cannot open directory '", 28);
		else
			ft_strlcpy(error, "ft_ls: cannot access '", 23);
		ft_strlcat(error, path, ft_strlen(path) + ft_strlen(error) + 1);
		ft_strlcat(error, "'", ft_strlen(error) + 2);
		perror(error);
		return (0);
	}
	new_dir = (t_dir *)malloc(sizeof(t_dir));
	if (!new_dir)
		return (-1);
	new_dir->dir = dir;
	new_dir->path = ft_strdup(path);
	tmp = ft_lstnew(new_dir);
	ft_lstadd_back(list, tmp);
	return (1);
}

static t_list	*dirs(char **dirs)
{
	t_list *(res) = NULL;
	DIR *(dir1) = NULL;
	int (i) = 0;
	while (dirs[i])
	{
		dir1 = opendir(dirs[i]);
		if (add_dir(&res, dir1, dirs[i]) < 0)
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
t_list	*get_directories(int ac, char *argv[], int dir_cnt)
{
	int (i) = 0;
	int (dirI) = 0;
	char **(dir_strs) = NULL;
	if (dir_cnt == 0)
	{
		dir_strs = (char **)malloc(sizeof(char *) * 2);
		if (!dir_strs)
			return (NULL);
		dir_strs[0] = ft_strdup(".");
		dir_strs[1] = NULL;
	}
	else {
		dir_strs = (char **)malloc(sizeof(char *) * (dir_cnt + 1));
		if (!dir_strs)
			return (NULL);
		dir_strs[dir_cnt] = NULL;
		while (++i < ac) {
			if (argv[i][0] != '-')
				dir_strs[dirI++] = ft_strdup(argv[i]);
		}
	}
	return (dirs(dir_strs));
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
			write(1, "ls: undefined option -- '", 25);
			ft_printf("%c", opt[j]);
			write(1, "'\n", 3);
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
		if (argv[i][0] == '-')
		{
			cnt++;
			fill_modes(argv[i], modes);
		}
	}
	return (cnt);
}
