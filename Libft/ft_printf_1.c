/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:06:32 by mkardes           #+#    #+#             */
/*   Updated: 2022/02/24 15:52:59 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_v2(int fd, char g)
{
	write(fd, &g, 1);
	return (1);
}

int	hex_print(int fd, unsigned int n, char c)
{
	int				i;
	int				i1;
	int				len;
	char			*a;
	unsigned int	n1;

	if (c == 'X')
		a = ft_strdup("0123456789ABCDEF");
	else
		a = ft_strdup("0123456789abcdef");
	i = 1;
	n1 = n;
	while (n1 >= 16 && i++)
		n1 = n1 / 16;
	len = i;
	while (--i >= 0)
	{
		n1 = n;
		i1 = i;
		while (--i1 >= 0)
			n1 = n1 / 16;
		ft_putchar_v2(fd, a[n1 % 16]);
	}
	free(a);
	return (len);
}

int	ptr_printer(int fd, unsigned long n)
{
	char	*a;

	a = ft_strdup("0123456789abcdef");
	if (n >= 16)
	{
		ptr_printer(fd, n / 16);
		ptr_printer(fd, n % 16);
	}
	else
		ft_putchar_v2(fd, a[n]);
	free(a);
	return (0);
}

int	ptr_print(int fd, unsigned long n)
{
	int	i;

	i = 1;
	ft_putchar_v2(fd, '0');
	ft_putchar_v2(fd, 'x');
	ptr_printer(fd, n);
	while (n >= 16)
	{
		n /= 16;
		i++;
	}
	return (i + 2);
}
