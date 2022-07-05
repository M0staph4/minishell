/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:03:06 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:49:53 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	x;

	i = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (i);
	j = ft_strlen(dst);
	if (dstsize == 0 || j > dstsize)
	{
		x = i + dstsize;
		return (x);
	}
	else
		x = i + j;
	i = 0;
	while (src[i] != '\0' && dstsize - 1 > j)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (x);
}
