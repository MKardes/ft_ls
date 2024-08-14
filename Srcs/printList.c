#include "ft_ls.h"
#include <time.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

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

static char	*getSize(int maxDigitCount, long size)
{
	int		i;
	int		digitCount;
	char	*res;
	char	*sizeStr;

	res = (char *)malloc(sizeof(char) * maxDigitCount + 1);
	if (!res)
		return (NULL);
	digitCount = digit_count(size);
	i = -1;
	while (++i < maxDigitCount - digitCount)
		res[i] = ' ';
	res[i] = '\0';
	sizeStr = ft_ltoa(size);
	ft_strlcat(res, sizeStr, ft_strlen(res) + ft_strlen(sizeStr) + 1);
	free(sizeStr);
	return (res);
}

static char	*addSpaces(char *str, long size)
{
	int		i;
	int		len;
	char	*res;
	char	*spcs;

	res = NULL;
	spcs = NULL;
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

void	printList(t_list *list, long *maxSize, long total, const char *path, int *nl_flag)
{
	t_file	*(c) = NULL;
	char *(fileNLink) = NULL;
	char *(fileSize) = NULL;
	int (maxDigitCountNLink) = digit_count(maxSize[0]);
	int (maxDigitCountSize) = digit_count(maxSize[3]);
	if (*nl_flag != 0)
		ft_printf("\n");
	else
		*nl_flag = 1;
	if (path)
		ft_printf("%s:\n", path);
	if (total == -1)
	{
		while (list)
		{
            c = list->content;
			ft_printf("%s  ", c->name);
			list = list->next;
		}
		ft_printf("\n");
		return ;
	}
	ft_printf("total %ld\n", total);
	while (list)
	{
		c = list->content;
		fileNLink = getSize(maxDigitCountNLink, c->nlink);
		fileSize = getSize(maxDigitCountSize, c->size);
		c->pw_name = addSpaces(c->pw_name, maxSize[1]);
		c->gr_name = addSpaces(c->gr_name, maxSize[2]);
		char *timeStr = ft_substr(ctime(&(c->time)), 4, 12);
		ft_printf("%s  %s %s  %s  %s %s %s\n", c->acm, fileNLink, c->pw_name, c->gr_name, fileSize, timeStr, c->name);
		free(timeStr);
		free(fileNLink);
		free(fileSize);
		list = list->next;
	}
}

void	printFile(const char *path, int isLFlag) {
	struct stat (status) = {};
	if (lstat(path, &status) < 0)
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", path, strerror(errno));
		return ;
	}
	if (isLFlag) {
		char *name = ft_strdup(path);
		char *acm = get_acm(status.st_mode);
		if (acm[0] == 'l')
		{
			char link_path[1024];
			int  byte = readlink(path, link_path, 1024);
			link_path[byte] = '\0'; 
			char *tmp = name;
			name = ft_strjoin(tmp, " -> ");
			free(tmp);
			tmp = name;
			name = ft_strjoin(tmp, link_path);
			free(tmp);
		}
		char *timeStr = ft_substr(ctime(&(status.st_mtim.tv_sec)), 4, 12);
		ft_printf("%s  %d %s  %s  %d %s %s\n",
			acm,
			status.st_nlink,
			getpwuid(status.st_uid)->pw_name,
			getgrgid(status.st_gid)->gr_name,
			status.st_size,
			timeStr,
			name);
		free(timeStr);
		free(name);
		free(acm);
	}
	else {
		ft_printf("%s\n", path);
	}
}