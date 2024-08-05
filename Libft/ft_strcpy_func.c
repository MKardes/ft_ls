/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:30:58 by mkardes           #+#    #+#             */
/*   Updated: 2022/02/08 08:36:41 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpy_func(char *dst, const char *src, int (*f)(int))
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = f(src[i]);
		i++;
	}
	dst[i] = 0;
	return (i);
}