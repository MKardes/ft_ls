#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>

//Hint: ls could be use with a file or folder

/* First */
//-R, --recursive /* First */
//    qqlist subdirectories recursively

//-l     use a long listing format
//          The -l option signifies the long list format.
//          This shows a lot more information presented to the user than the standard command. You will see the file permissions,
//          the number of links, owner name, owner group, file size, time of last modification, and the file or directory name. 
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


typedef struct dirent* dirPoint;
#include <limits.h>
int main(int ac, char *argv[])
{
    if (ac < 1)
        return -1;
    if (ac == 1)
    {
        // the file is "."
    }
    else
    {
        // there is a loop to list all the arguments
    }
    DIR *dir1 = opendir(argv[1]);
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
        struct stat status;
        stat(dir->d_name, &status);
        struct passwd *userInf = getpwuid(status.st_uid);
        struct group *groupInf = getgrgid(status.st_gid);
        char *date = ctime(&status.st_mtim.tv_sec);
        date[ft_strlen(date) - 1] = '\0';
        ft_printf("%d %ld\t%s\t%s %d %s %s\n", status.st_mode, status.st_nlink, userInf->pw_name, groupInf->gr_name, status.st_size, date, dir->d_name);
        //free(userInf);
        dir = readdir(dir1);
    }
    //printf("%s\n",dir1->d_name);
}