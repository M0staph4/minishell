/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:14:02 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/19 02:32:32 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s1;
	size_t	len;

	s1 = (char *)s;
	len = ft_strlen(s1) + 1;
	i = 0;
	while (i < len)
	{
		if (*s1 == (char)c)
			return (s1);
		s1++;
		i++;
	}
	return (NULL);
}
