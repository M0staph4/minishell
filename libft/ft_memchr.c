/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:58:49 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 17:58:54 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) str;
	i = 0;
	if (n == 0)
		return (NULL);
	while (n > i)
	{
		if (p[i] == (unsigned char) c)
			return (&p[i]);
		i++;
	}
	return (0);
}
