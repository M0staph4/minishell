/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:59:13 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 17:59:16 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*i1;
	unsigned char	*i2;

	i1 = (unsigned char *) str1;
	i2 = (unsigned char *) str2;
	while (n > 0)
	{
		if (*i1 != *i2)
			return ((unsigned int) *i1 - (unsigned int) *i2);
		i1++;
		i2++;
		n--;
	}
	return (0);
}
