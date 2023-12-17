#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>

static int	digit_count(long n)
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

static char *getSize(int maxDigitCount, long size)
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

static char *addSpaces(char *str, long size)
{
    int     i;
    int     len;
    char    *res = NULL;
    char    *spcs = NULL;

    if (size <= (long)ft_strlen(str))
        return (str);
    len = size - ft_strlen(str);
    spcs = (char *)malloc(sizeof(char) * (len + 1));
    spcs[len] = '\0';
    i = -1;
    while (++i < len) 
        spcs[i] = ' ';
    res = ft_strjoin(str, spcs);
    free(spcs);
    free(str);
    return (res);
}

static void printList(t_list *list, long maxSize[3], long total)
{
    int         maxDigitCount;
    char*       fileSize;
    t_listF*    c = NULL;
    
    maxDigitCount = digit_count(maxSize[2]);
    ft_printf("total %ld\n", total);
    while (list)
    {
        c = list->content;
        fileSize = getSize(maxDigitCount, c->size);
        c->pw_name = addSpaces(c->pw_name, maxSize[0]);
        c->gr_name = addSpaces(c->gr_name, maxSize[1]);
        ft_printf("%s %ld %s %s %s %s %s\n", c->acm, c->nlink, c->pw_name, c->gr_name, fileSize, c->date, c->name);
        free(fileSize);
        list = list->next;
    }
}

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

static void    listAddBack(t_list **list, const char *path, dirPoint dir, long *maxSize, long *total)
{
    struct stat status;
    char        *tmp1 = ft_strjoin(path, "/");
    char        *tmp2 = ft_strjoin(tmp1, dir->d_name);
    if (stat(tmp2, &status) < 0)
    {
        ft_printf("Status info couldn't be taken!\n");
        return ;
    }
    free(tmp1);
    free(tmp2);
    struct passwd*  userInf = getpwuid(status.st_uid);
    struct group*   groupInf = getgrgid(status.st_gid);
    t_list          *tmp = NULL; 
    t_listF         *obj = NULL;

    obj = (t_listF *)malloc(sizeof(t_listF));
    obj->acm = getAcm(status.st_mode);
    obj->nlink = status.st_nlink;
    obj->pw_name = ft_strdup(userInf->pw_name);
    if (maxSize[0] < (long)ft_strlen(obj->pw_name))
        maxSize[0] = (long)ft_strlen(obj->pw_name);
    obj->gr_name = ft_strdup(groupInf->gr_name);
    if (maxSize[1] < (long)ft_strlen(obj->gr_name))
        maxSize[1] = (long)ft_strlen(obj->gr_name);
    obj->size = status.st_size;
    if (maxSize[2] < obj->size)
        maxSize[2] = obj->size;
    obj->date = ft_substr(ctime(&status.st_mtim.tv_sec), 4, 13);
    obj->date[ft_strlen(obj->date) - 1] = '\0';
    obj->name = ft_strdup(dir->d_name);
    tmp = ft_lstnew(obj);
    ft_lstadd_back(list, tmp);
    *total += status.st_blocks / 2;
}

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

void    delList(void *e)
{
    t_listF* arg = (t_listF*)e;
    free(arg->acm);
    free(arg->pw_name);
    free(arg->gr_name);
    free(arg->date);
    free(arg->name);
}

int ls(const char *modes, t_dir *directory)
{
    long    maxSize[3] = {0,0,0};
    long    total = 0;
    t_list* list = NULL;

    dirPoint dir = readdir(directory->dir);
    while(dir)
    {
        // size için hepsinin size ını bilip ona göre listele(hizalamak için)
        if (dir->d_name[0] == '.' && modes[0] != 'a')
        {
            dir = readdir(directory->dir);
            continue ;
        }
        if (modes[1] == 'l')
            listAddBack(&list, directory->path, dir, maxSize, &total);
        else
            ft_printf("%s  ", dir->d_name);
        //free(userInf);
        dir = readdir(directory->dir);
    }
    if (modes[1] == 'l')
        printList(list, maxSize, total);
    else
        ft_printf("\n");
    ft_lstclear(&list, &delList);
    return(0);
}
