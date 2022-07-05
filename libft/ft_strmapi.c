/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:43:40 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:45:36 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*k;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	k = malloc (i + 1);
	if (k == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		k[i] = f(i, s[i]);
		i++;
	}
	k[i] = '\0';
	return (k);
}
