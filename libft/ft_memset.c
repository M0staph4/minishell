/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:00:41 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:31:14 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*o;
	char			y;
	int				i;

	o = (unsigned char *) b;
	y = (char) c;
	i = 0;
	while (len > 0)
	{
		o[i] = y;
		len--;
		i++;
	}
	return (o);
}
