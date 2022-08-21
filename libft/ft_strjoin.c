/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:12:51 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/15 23:26:02 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*ft_strcpy(char *dst, const char *src)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int i;
	int j;

	j = 0;
	i = -1;
	if (!s1 || !s2)
		return (0);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result)
	{
		while(s1[++i])
			result[i] = s1[i];
		while(s2[j])
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	return (result);
}
