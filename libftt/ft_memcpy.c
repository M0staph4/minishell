/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:59:42 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:27:12 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p;
	char	*y;
	size_t	i;

	i = 0;
	p = (char *) dst;
	y = (char *) src;
	if (n == 0)
		return ((char *) dst);
	if (p == y)
		return (p);
	if (p != NULL || y != NULL)
	{
		while (n > i)
		{
			p[i] = y[i];
			i++;
		}
		return ((unsigned char *) dst);
	}
	return (0);
}
