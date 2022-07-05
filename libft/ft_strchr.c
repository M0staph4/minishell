/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:01:38 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 18:01:41 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	ch;
	size_t	i;

	ch = (char) c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
		{
			return (&((char *)str)[i]);
		}
		i++;
	}
	if (str[i] == ch)
		return (&((char *)str)[i]);
	return (NULL);
}
