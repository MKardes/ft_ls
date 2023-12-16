#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>

//#include <sys/stat.h>
//File Type Bits (Higher-order bits):
//S_IFREG: Regular file       -: Regular file
//S_IFDIR: Directory          d: Directory
//S_IFCHR: Character device   c: Character device
//S_IFBLK: Block device       b: Block device
//S_IFIFO: FIFO (named pipe)  p: FIFO (named pipe)
//S_IFLNK: Symbolic link      l: Symbolic link
//S_IFSOCK: Socket            s: Socket
//Permission Bits (Lower-order bits):
//S_IRUSR, S_IWUSR, S_IXUSR: Owner's read, write, and execute permissions => S_IRWXU
//S_IRGRP, S_IWGRP, S_IXGRP: Group's read, write, and execute permissions => S_IRWXG
//S_IROTH, S_IWOTH, S_IXOTH: Others' read, write, and execute permissions => S_IRWXO

char* getAcm(int n)
{
    int i;
    char acm[11];
    
    i = -1;
    acm[10] = '\0';
    while (++i < 10)
        acm[i] = '-';
    if (S_ISDIR(n))
        acm[0] = 'd';
    else if (S_ISCHR(n))
        acm[0] = 'c';
    else if (S_ISBLK(n))
        acm[0] = 'b';
    else if (S_ISFIFO(n))
        acm[0] = 'p';
    else if (S_ISLNK(n))
        acm[0] = 'l';
    else if (S_ISSOCK(n))
        acm[0] = 's';
    if (n & S_IRUSR)
        acm[1] = 'r';
    if (n & S_IWUSR)
        acm[2] = 'w';
    if (n & S_IXUSR)
        acm[3] = 'x';
    if (n & S_IRGRP)
        acm[4] = 'r';
    if (n & S_IWGRP)
        acm[5] = 'w';
    if (n & S_IXGRP)
        acm[6] = 'x';
    if (n & S_IROTH)
        acm[7] = 'r';
    if (n & S_IWOTH)
        acm[8] = 'w';
    if (n & S_IXOTH)
        acm[9] = 'x';
    return(ft_strdup(acm));
}