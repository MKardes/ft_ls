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
	t_list	*files;
	t_list	*root;
	char	modes[MAX_MODES];
	int		flag_cnt;
	int		dir_cnt;
	int		regFile_cnt;
	int		res;
	int		flag;
	int		nl_flag;

	res = 0;
	flag = 0;
	nl_flag = 0;
	dir_cnt = 0;
	regFile_cnt = 0;
	flag_cnt = get_flags(ac, argv, modes);
	files = get_files(ac, argv, ac - flag_cnt - 1, &dir_cnt);
	regFile_cnt = ac - flag_cnt - 1 - dir_cnt;
	sortList(&files, modes, 1);
	if (!files)
		return (-1);
	root = files;
	if (!(dir_cnt + regFile_cnt == 0 || dir_cnt + regFile_cnt == 1))
		flag = 1;
	else if (modes[2] == 'R')
		flag = 2;
	while (files)
	{
		if (!((t_dir *)(files->content))->dir) 
			res = ls(modes, (t_dir *)files->content, flag, &nl_flag);
		files = files->next;
	}
	if (regFile_cnt > 0 && dir_cnt > 0)
		ft_printf("\n");
	files = root;
	while (files)
	{
		if (((t_dir *)(files->content))->dir)
			res = ls(modes, (t_dir *)files->content, flag, &nl_flag);
		files = files->next;
	}
	ft_lstclear(&root, &del_dirs);
	return (res);
}

// -R  			      tot      a: tot     b: tot    (f_cnt = 1 && -R present)   flag = 2
// -R arg             tot 	   a: tot     b: tot    (f_cnt = 1 && -R present)   flag = 2
// arg arg arg        a: tot   b: tot     c: tot    (f_cnt != 1 && -R !present) flag = 1
// -R arg arg arg     a: tot   b: tot     c: tot    (f_cnt != 1 && -R present)  flag = 1
// ...												(f_cnt = 1 && -R !present)	flag = 0