#ifndef FT_LS_H
# define FT_LS_H

typedef struct s_listF {
    char*   acm;
    long    nlink;
    char*   pw_name;
    char*   gr_name;
    long    size;
    char*   date;
    char*   name;
} t_listF;

#endif
