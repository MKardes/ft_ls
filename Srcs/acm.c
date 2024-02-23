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
//S_IRUSR, S_IWUSR, S_IXUSR: Owner's read, write, and execute permissions
//For all permissions => S_IRWXU
//S_IRGRP, S_IWGRP, S_IXGRP: Group's read, write, and execute permissions
//For all permissions => S_IRWXG
//S_IROTH, S_IWOTH, S_IXOTH: Others' read, write, and execute permissions
//For all permissions => S_IRWXO

static void	set_type(char *acm, int n)
{
	if (S_ISDIR(n))
		acm[0] = 'd';
	if (S_ISCHR(n))
		acm[0] = 'c';
	if (S_ISBLK(n))
		acm[0] = 'b';
	if (S_ISFIFO(n))
		acm[0] = 'p';
	if (S_ISLNK(n))
		acm[0] = 'l';
	if (S_ISSOCK(n))
		acm[0] = 's';
}

char	*get_acm(int n)
{
	char	acm[11];

	ft_memset(acm, '-', 10);
	acm[10] = '\0';
	set_type(acm, n);
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
	return (ft_strdup(acm));
}
