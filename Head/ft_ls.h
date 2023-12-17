#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <stdbool.h>

# define MAX_MODES 5
// [0] = -a, [1] = -l, [2] = -R, [3] = -r, [4] = -t

typedef struct s_listF {
    char*   acm;
    long    nlink;
    char*   pw_name;
    char*   gr_name;
    long    size;
    char*   date;
    char*   name;
} t_listF;

typedef struct s_dir {
    DIR*    dir;
    char*   path;
} t_dir;

typedef struct dirent* dirPoint;

/* acm.c */
char* getAcm(int n);

/* getArgs.c */
t_list  *getDirectories(int ac, char *argv[], int dir_cnt);
int     getFlags(int ac, char *argv[], char *modes);

/* ls.c */
int ls(const char *modes, t_dir *directory, bool flag);

/* main.c */
void    delDirs(void *e);

#endif
