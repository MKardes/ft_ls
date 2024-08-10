#include "ft_ls.h"
#include <time.h>

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

void	printList(t_list *list, long maxSize[4], long total, const char *path)
{
	t_file	*(c) = NULL;
	char *(fileNLink) = NULL;
	char *(fileSize) = NULL;
	int (maxDigitCountNLink) = digit_count(maxSize[0]);
	int (maxDigitCountSize) = digit_count(maxSize[3]);
	if (path)
		ft_printf("\n%s:\n", path);
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
		ft_printf("%s  %s %s  %s  %s %s %s\n", c->acm, fileNLink, c->pw_name, c->gr_name, fileSize, timeStr/* c->date */, c->name);
		free(timeStr);
		free(fileNLink);
		free(fileSize);
		list = list->next;
	}
}