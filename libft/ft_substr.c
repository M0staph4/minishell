/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:05:48 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/19 02:31:56 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char	const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;
	size_t		size;

	i = 0;
	size = len;
	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s) || s[0] == '\0')
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		size = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
