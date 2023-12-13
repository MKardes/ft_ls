#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#define MAX_MODES 5
// [0] = -a, [1] = -l, [2] = -R, [3] = -r, [4] = -t

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


//◦ write

//#include <dirent.h>
//◦ opendir
//      DIR *opendir(const char *name);
//      Description
//          The opendir() function opens a directory stream corresponding to the directory name, and returns a 
//          pointer to the directory stream. The stream is positioned at the first entry in the directory.
//      Return Value
//          The opendir() and fdopendir() functions return a pointer to the directory stream. On error, NULL is
//          returned, and errno is set appropriately.
//◦ readdir
//          struct dirent *readdir(DIR *dirp);
//          struct dirent {
//             ino_t          d_ino;       /* Inode number */
//             off_t          d_off;       /* Not an offset; see below */
//             unsigned short d_reclen;    /* Length of this record */
//             unsigned char  d_type;      /* Type of file; not supported
//                                            by all filesystem types */
//             char           d_name[256]; /* Null-terminated filename */
//         };
//      Description
//          The readdir() function returns a pointer to a dirent structure
//          representing the next directory entry in the directory stream
//          pointed to by dirp.  It returns NULL on reaching the end of the
//          directory stream or if an error occurred.

//◦ closedir
//      Description
//          The closedir() function closes the directory stream associated with dirp. A successful call to closedir()
//          also closes the underlying file descriptor associated with dirp. The directory stream descriptor dirp is
//          not available after this call.
//      Return Value
//          The closedir() function returns 0 on success. On error, -1 is returned, and errno is set appropriately.

//#include <sys/stat.h>
//◦ stat
//      int stat(const char *restrict pathname,
//               struct stat *restrict statbuf);(-1 on error and errno filled, ortherwise 0)
//◦ lstat
//      int lstat(const char *restrict pathname,
//                struct stat *restrict statbuf);
//      DESCRIPTION       
//          These functions return information about a file, in the buffer
//          pointed to by statbuf.  No permissions are required on the file
//          itself, but—in the case of stat(), fstatat(), and lstat()—execute
//          (search) permission is required on all of the directories in
//          pathname that lead to the file.
//
//          stat() and fstatat() retrieve information about the file pointed
//          to by pathname; the differences for fstatat() are described
//          below.
//
//          lstat() is identical to stat(), except that if pathname is a
//          symbolic link, then it returns information about the link itself,
//          not the file that the link refers to.

//      struct stat {
//          dev_t      st_dev;      /* ID of device containing file (int)*/
//          ino_t      st_ino;      /* Inode number */
//          mode_t     st_mode;     /* File type and mode */
//          nlink_t    st_nlink;    /* Number of hard links */
//          uid_t      st_uid;      /* User ID of owner */
//          gid_t      st_gid;      /* Group ID of owner */
//          dev_t      st_rdev;     /* Device ID (if special file) */
//          off_t      st_size;     /* Total size, in bytes */
//          blksize_t  st_blksize;  /* Block size for filesystem I/O */
//          blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */
//  
//          struct timespec  st_atim;  /* Time of last access */
//          struct timespec  st_mtim;  /* Time of last modification */
//          struct timespec  st_ctim;  /* Time of last status change */
//
//      #define st_atime  st_atim.tv_sec  /* Backward compatibility */
//      #define st_mtine  st_mtim.tv_sec
//      #define st_ctime  st_ctim.tv_sec
//      };

//#include <pwd.h>
//#include <errno.h>
//◦ getpwuid
//      errno = 0;(to make gerpwuid has no error: https://man7.org/linux/man-pages/man3/getpwuid.3p.html)
//      struct passwd *getpwuid(uid_t uid);
//      DESCRIPTION
//          The getpwuid() function shall search the user database for an
//          entry with a matching uid.
//      RETURN VALUE         top
//          The getpwuid() function shall return a pointer to a struct passwd
//          with the structure as defined in <pwd.h> with a matching entry if
//          found. A null pointer shall be returned if the requested entry is
//          not found, or an error occurs. If the requested entry was not
//          found, errno shall not be changed. On error, errno shall be set
//          to indicate the error.
//      struct passwd {
//          char   *pw_name;       /* username */
//          char   *pw_passwd;     /* user password */
//          uid_t   pw_uid;        /* user ID */
//          gid_t   pw_gid;        /* group ID */
//          char   *pw_gecos;      /* user information */
//          char   *pw_dir;        /* home directory */
//          char   *pw_shell;      /* shell program */
//      };

// #include <grp.h>
//◦ getgrgid
//      errno = 0;(to make gerpwuid has no error: https://man7.org/linux/man-pages/man3/getgrgid.3p.html)
//      struct group *getgrgid(gid_t gid);
//      (very similar to getpwuid)
//      struct group {
//          char   *gr_name;        /* group name */
//          char   *gr_passwd;      /* group password */
//          gid_t   gr_gid;         /* group ID */
//          char  **gr_mem;         /* NULL-terminated array of pointers
//                                      to names of group members */
//      };

//◦ getfattr -d -m - /path/to/your/file


//◦ getxattr

//#include <time.h>
//◦ time
//◦ ctime
//      char *ctime(const time_t *timep);
//      DESCRIPTION         top
//             The ctime(), gmtime(), and localtime() functions all take an
//             argument of data type time_t, which represents calendar time.
//             When interpreted as an absolute time value, it represents the
//             number of seconds elapsed since the Epoch, 1970-01-01 00:00:00
//             +0000 (UTC).
//      
//             The asctime() and mktime() functions both take an argument
//             representing broken-down time, which is a representation
//             separated into year, month, day, and so on.
//      
//             Broken-down time is stored in the structure tm, described in
//             tm(3type).
//      
//             The call ctime(t) is equivalent to asctime(localtime(t)).  It
//             converts the calendar time t into a null-terminated string of the
//             form
//      
//                 "Wed Jun 30 21:49:08 1993\n"

//◦ readlink

//◦ perror

//◦ strerror

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

typedef struct dirent* dirPoint;
#include <limits.h>

void getFlags(int ac, char *argv[], char *modes) {
    int i;
    int j;

    i = 0;
    while (i < MAX_MODES)
    {
        modes[i] = '-';
        i++;
    }
    i = 0;
    while (i < ac)
    {
        if (argv[i][0] == '-')
        {
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
}

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

void    listAddBack(t_list **list, dirPoint dir, long *maxSize, long *total){
    struct stat status;
    stat(dir->d_name, &status);
    struct passwd*  userInf = getpwuid(status.st_uid);
    struct group*   groupInf = getgrgid(status.st_gid);
    t_list          *tmp = NULL; 
    t_listF         *obj = NULL;

    obj = (t_listF *)malloc(sizeof(t_listF));
    obj->acm = getAcm(status.st_mode);
    obj->nlink = status.st_nlink;
    obj->pw_name = ft_strdup(userInf->pw_name);
    obj->gr_name = ft_strdup(groupInf->gr_name);
    obj->size = status.st_size;
    if (*maxSize < obj->size)
        *maxSize = obj->size;
    obj->date = ft_substr(ctime(&status.st_mtim.tv_sec), 4, 13);
    obj->date[ft_strlen(obj->date) - 1] = '\0';
    obj->name = ft_strdup(dir->d_name);
    tmp = ft_lstnew(obj);
    ft_lstadd_back(list, tmp);
    *total += status.st_blocks / 2;
}

int	digit_count(long n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char *getSize(int maxDigitCount, long size)
{
    int     i;
    int     digitCount;
    char    *res = NULL;
    char    *sizeStr;

    res = (char *)malloc(sizeof(char) * maxDigitCount + 1);
    digitCount = digit_count(size);
    i = -1;
    while (++i < maxDigitCount - digitCount)
        res[i] = ' ';
    res[i] = '\0';
    sizeStr = ft_ltoa(size);
    ft_strlcat(res, sizeStr, ft_strlen(res) + ft_strlen(sizeStr) + 1);
    free(sizeStr);
    return res;
}

void printList(t_list *list, long maxSize, long total)
{
    int         maxDigitCount;
    char*       fileSize;
    t_listF*    c = NULL;
    
    maxDigitCount = digit_count(maxSize);
    ft_printf("total %ld\n", total);
    while (list)
    {
        c = list->content;
        fileSize = getSize(maxDigitCount, c->size);
        ft_printf("%s %ld %s %s %s %s %s\n", c->acm, c->nlink, c->pw_name, c->gr_name, fileSize, c->date, c->name);
        free(fileSize);
        list = list->next;
    }
}

void listRecursive(int i)
{
    listRecursive(i);
}

int main(int ac, char *argv[])
{
    char modes[MAX_MODES];

    getFlags(ac, argv, modes);
    //if (ac < 1)
    //    return -1;
    //if (ac == 1)
    //{
    //    // the file is "."
    //    list(1, argv, "-----");
    //}
    //else
    //{
    //    // there is a loop to list all the arguments
    //    list(ac, argv, modes);
    //}
    DIR*    dir1 = opendir(argv[1]);
    long    maxSize = 0;
    long    total = 0;
    t_list* list = NULL;
    if (!dir1)
    {
        char error[100] = "ft_ls: cannot access '";
        ft_strlcat(error, argv[1], ft_strlen(argv[1]) + 22);
        ft_strlcat(error, "'", ft_strlen(argv[1]) + 25);
        perror(error);
        exit(2);// temporarly but return value is 2
    }
    dirPoint dir = readdir(dir1);
    while(dir)
    {
        // size için hepsinin size ını bilip ona göre listele(hizalamak için)
        if (dir->d_name[0] == '.' && modes[0] != 'a')
        {
            dir = readdir(dir1);
            continue ;
        }
        if (modes[1] == 'l')
            listAddBack(&list, dir, &maxSize, &total);
        else
            ft_printf("%s  ", dir->d_name);
        //free(userInf);
        dir = readdir(dir1);
    }
    if (modes[1] == 'l')
        printList(list, maxSize, total);
    else
        ft_printf("\n");
}