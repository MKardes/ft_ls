#include "libft.h"
#include "ft_ls.h"

//Hint: ls could be use with a file or folder

/* First */
//-R, --recursive /* First */
//    qqlist subdirectories recursively

//-l     use a long listing format
//			The -l option signifies the long list format.
//			This shows a lot more information presented to the user than the
//			standard command. You will see the file permissions, the number of
//			links, owner name, owner group, file size, time of last
//			modification, and the file or directory name.
//			> What 'total 8' stands for?
//			> Thank you very much.
//			That is the total number of file system blocks, including indirect
//			blocks, used by the listed files.  If you run "ls -s" on the same
//			files and sum the reported numbers you'll get that same number.

//-a, --all
//    do not ignore entries starting with .

//-r, --reverse
//    reverse order while sorting

//-t     sort by time, newest first; see --time

//You do not have to deal with the multiple column format for the exit when
//the option -l isn’t in the arguments

//	You are not required to deal with ACL 
//	and extended attributes. --> Access Control List

int	main(int ac, char *argv[])
{
	t_list	*directories;
	t_list	*root;
	char	modes[MAX_MODES];
	int		f_cnt;
	int		res;
	bool	flag;

	res = 0;
	flag = 1;
	f_cnt = get_flags(ac, argv, modes);
	directories = get_directories(ac, argv, ac - f_cnt - 1);
	sortList(&directories, modes, 1);
	if (!directories)
		return (-1);
	root = directories;
	if ((ac - f_cnt - 1 == 0 || ac - f_cnt - 1 == 1) && modes[2] != 'R')
		flag = 0;
	while (directories)
	{
		res = ls(modes, (t_dir *)directories->content, flag);
		directories = directories->next;
	}
	ft_lstclear(&root, &del_dirs);
	return (res);
}
