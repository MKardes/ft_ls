#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <stdbool.h>

# define MAX_MODES 5
// [0] = -a, [1] = -l, [2] = -R, [3] = -r, [4] = -t

typedef struct s_listF {
    char*   name;
    char*   date;
    char*   acm;
    long    nlink;
    char*   pw_name;
    char*   gr_name;
    long    size;
} t_listF;

typedef struct s_dir {
    DIR*    dir;
    char*   path;
} t_dir;

typedef struct dirent* dirPoint;

/* acm.c */
char* get_acm(int n);

/* getArgs.c */
t_list  *get_directories(int ac, char *argv[], int dir_cnt);
int     get_flags(int ac, char *argv[], char *modes);

/* utils.c */
char* getPath(const char* dir_path, const char*  dir_name);

/* printList.c */
void	printList(t_list *list, long maxSize[3], long total, const char *path);

/* ls.c */
int ls(const char *modes, t_dir *directory, bool flag);

/* main.c */
void    del_dirs(void *e);
void	del_list(void *e);

#endif
