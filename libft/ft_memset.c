/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:59:13 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/14 21:33:36 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*buffer;
	size_t	i;

	i = 0;
	buffer = (char *)b;
	while (i < len)
	{
		buffer[i] = (unsigned char)c;
		i++;
	}
	return (buffer);
}
