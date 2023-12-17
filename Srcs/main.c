#include "libft.h"
#include "ft_ls.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>



//Hint: ls could be use with a file or folder

/* First */
//-R, --recursive /* First */
//    qqlist subdirectories recursively

//-l     use a long listing format
//          The -l option signifies the long list format.
//          This shows a lot more information presented to the user than the standard command. You will see the file permissions,
//          the number of links, owner name, owner group, file size, time of last modification, and the file or directory name. 
//
//          > What 'total 8' stands for?
//          > Thank you very much.
//          That is the total number of file system blocks, including indirect
//          blocks, used by the listed files.  If you run "ls -s" on the same
//          files and sum the reported numbers you'll get that same number.

//-a, --all
//    do not ignore entries starting with .

//-r, --reverse
//    reverse order while sorting

//-t     sort by time, newest first; see --time


//You do not have to deal with the multiple column format for the exit when
//the option -l isn’t in the arguments

//You are not required to deal with ACL and extended attributes. --> Access Control List


//◦ getfattr -d -m - /path/to/your/file


//◦ getxattr


//◦ readlink

//◦ perror

//◦ strerror

void listRecursive(int i)
{
    listRecursive(i);
}

void    delDirs(void *e)
{
    t_dir* arg = (t_dir*)e;
    closedir(arg->dir);
    free(arg->path);
    free(arg);
}

int main(int ac, char *argv[])
{
    t_list  *directories;
    char    modes[MAX_MODES];
    int     f_cnt;
    int     res = 0;
    bool    flag = 1;

    f_cnt = getFlags(ac, argv, modes);
    directories = getDirectories(ac, argv, ac - f_cnt - 1);
    if (!directories)
        return(-1);
    if ((ac - f_cnt - 1 == 0 || ac - f_cnt - 1 == 1) && modes[2] != 'R')
        flag = 0;
    while (directories)
    {
        res = ls(modes, (t_dir *)directories->content, flag);
        directories = directories->next;
    }
    ft_lstclear(&directories, &delDirs);
    return(res);
}