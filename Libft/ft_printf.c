/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:06:49 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/14 14:37:31 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bas_say(unsigned int c)
{
	int	i;

	i = 0;
	while (c >= 10)
	{
		c = c / 10;
		i++;
	}
	return (i + 1);
}

int	array_print(int fd, char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (array_print(fd, "(null)"));
	while (str[len])
		len += ft_putchar_v2(fd, str[len]);
	return (len);
}

int	ft_uitoa(int fd, unsigned int a)
{
	int		len;
	char	*str;

	len = ft_bas_say(a);
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = a % 10 + 48;
		a = a / 10;
		len--;
	}
	len = array_print(fd, str);
	free(str);
	return (len);
}

int	ft_strchecker(va_list arg, int g, int fd)
{
	char	*a;
	int		len;

	len = 0;
	if (g == 'c')
		len += ft_putchar_v2(fd, va_arg(arg, int));
	if (g == 's')
		len += array_print(fd, va_arg(arg, char *));
	if (g == 'p')
		len += ptr_print(fd, va_arg(arg, unsigned long));
	if (g == 'd' || g == 'i')
	{
		a = ft_itoa(va_arg(arg, int));
		len += array_print(fd, a);
		free(a);
	}
	if (g == 'l')
	{
		a = ft_ltoa(va_arg(arg, long));
		len += array_print(fd, a);
		free(a);
	}
	if (g == 'u')
		len += ft_uitoa(fd, va_arg(arg, unsigned int));
	if (g == 'x' || g == 'X')
		len += hex_print(fd, va_arg(arg, unsigned int), g);
	if (g == '%')
		len += ft_putchar_v2(fd, '%');
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	arg;
	int		len;
	int		i;

	va_start(arg, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_strchecker(arg, str[i], fd);
			if (str[i] == 'l')
				i++;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		len;
	int		i;

	va_start(arg, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_strchecker(arg, str[i], 1);
			if (str[i] == 'l')
				i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}
