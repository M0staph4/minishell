/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:00:36 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/15 14:11:55 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lend;
	size_t	lens;
	char	*src1;

	src1 = (char *)src;
	lend = ft_strlen(dst);
	lens = ft_strlen(src1);
	i = 0;
	if (dstsize <= lend)
		return (lens + dstsize);
	while (i < dstsize - 1 - lend && src[i])
	{
		dst[lend + i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[lend + i] = '\0';
	return (lend + lens);
}
