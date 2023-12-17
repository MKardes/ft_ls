#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# define MAX_MODES 5

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
int ls();

#endif
