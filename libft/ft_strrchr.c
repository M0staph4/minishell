/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:05:12 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 18:05:17 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	x;

	x = (char) c;
	i = 0;
	while (str[i] != '\0')
		i++;
	if (x == str[i])
		return (&((char *) str)[i]);
	while (i >= 0)
	{
		if (str[i] == x)
			return (&((char *) str)[i]);
		i--;
	}
	return (NULL);
}
