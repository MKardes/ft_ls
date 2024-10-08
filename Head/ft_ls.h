#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <stdbool.h>

# define MAX_MODES 5

# ifdef __linux__
#  define STAT_TIME st_mtim
# else
#  define STAT_TIME st_mtimespec
# endif

# define MAX_MODES 5
# define MODES "alRrt"
// [0] = -a, [1] = -l, [2] = -R, [3] = -r, [4] = -t

typedef struct s_file {
    char*   name;
    time_t	time;
	long	ntime;
    char*   acm;
    long    nlink;
    char*   pw_name;
    char*   gr_name;
    long    size;
} t_file;

typedef struct s_dir {
    char*   path;
    time_t	time;
	long	ntime;
    DIR*    dir;
} t_dir;

typedef struct dirent* dirPoint;

/* acm.c */
char* get_acm(int n);

/* getArgs.c */
t_list	*get_files(int ac, char *argv[], int file_cnt, int *dir_cnt);
int     get_flags(int ac, char *argv[], char *modes);

/* utils.c */
char* getPath(const char* dir_path, const char*  dir_name);
void sortList(t_list **list, const char *modes, char type);
t_dir* openDir(char* dir_path);

/* printList.c */
void	printList(t_list *list, long maxSize[3], long total, const char *path, int *nl_flag);
void	printFile(const char *path, int isLFlag);

/* ls.c */
int ls(const char *modes, const t_dir *directory, int flag, int *nl_flag);

/* del.c */
void	del_dirs(void *e);
void    delLList(void *e);

#endif
