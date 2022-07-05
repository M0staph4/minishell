/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:00:15 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:53:18 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*i1;
	const char	*i2;
	size_t		i;

	i1 = (char *) dst;
	i2 = (const char *) src;
	i = 0;
	if (i1 != NULL || i2 != NULL)
	{
		if (i1 > i2)
			while (len-- > 0)
				i1[len] = i2[len];
		else
			ft_memcpy(i1, i2, len);
		return (i1);
	}
	return (0);
}
