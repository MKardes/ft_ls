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
static t_list  *dirs(char **dirs)
{
    t_list* res = NULL;
    t_list* tmp = NULL;
    DIR*    open = NULL;
    t_dir*  dir = NULL;
    int     i;
    
    i = 0;
    while (dirs[i])
    {
        open = opendir(dirs[i]);
        if (!open)
        {
            char error[100];
            if (errno == EACCES)
                ft_strlcpy(error, "ft_ls: cannot open directory '", 28);
            else
                ft_strlcpy(error, "ft_ls: cannot access '", 23);
            ft_strlcat(error, dirs[i], ft_strlen(dirs[i]) + ft_strlen(error) + 1);
            ft_strlcat(error, "'", ft_strlen(error) + 2);
            perror(error);
        }
        else
        {
            dir = (t_dir *)malloc(sizeof(t_dir));
            if (!dir)
                return (NULL);
            dir->dir = open;
            dir->path = ft_strdup(dirs[i]);
            tmp = ft_lstnew(dir);
            ft_lstadd_back(&res, tmp);
        }
        i++;
    }
    i = -1;
    while (dirs[++i])
        free(dirs[i]);
    free(dirs);
    return (res);
}

// checks if a directory or file present in arguments
t_list  *getDirectories(int ac, char *argv[], int dir_cnt) {
    int     i;
    int     dirI;
    char    **dir_strs = NULL;

    if (dir_cnt == 0)
    {
        dir_strs = (char **)malloc(sizeof(char *) * 2);
        if (!dir_strs)
            return(NULL);
        dir_strs[0] = ft_strdup(".");
        dir_strs[1] = NULL;
        return(dirs(dir_strs));
    }
    dir_strs = (char **)malloc(sizeof(char *) * (dir_cnt + 1));
    if (!dir_strs)
        return(NULL);
    dir_strs[dir_cnt] = NULL;
    i = 0;
    dirI = 0;
    while (++i < ac)
        if (argv[i][0] != '-')
            dir_strs[dirI++] = ft_strdup(argv[i]);
    return(dirs(dir_strs));
}

// gets mode flags and returns number of mode arguments
int getFlags(int ac, char *argv[], char *modes) {
    int i;
    int j;
    int cnt;

    i = 0;
    while (i < MAX_MODES)
    {
        modes[i] = '-';
        i++;
    }
    cnt = 0;
    i = 1;
    while (i < ac)
    {
        if (argv[i][0] == '-')
        {
            cnt++;
            j = 1;
            while (argv[i][j])
            {
                if (argv[i][j] == 'a')
                    modes[0] = 'a';
                else if (argv[i][j] == 'l')
                    modes[1] = 'l';
                else if (argv[i][j] == 'R')
                    modes[2] = 'R';
                else if (argv[i][j] == 'r')
                    modes[3] = 'r';
                else if (argv[i][j] == 't')
                    modes[4] = 't';
                else
                {
                    write(2, "ls: option requires an argument -- '", 36);
                    ft_printf("%c", argv[i][j]);
                    write(2, "'\n", 3);
                    exit(2);
                }
                j++;
            }
        }
        i++;
    }
    return (cnt);
}