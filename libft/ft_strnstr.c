/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:39:59 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/15 23:27:24 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*haystack, const char	*needle, size_t	len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (*needle == 0)
		return ((char *)haystack);
	j = 0;
	while (j < len && haystack[j])
	{
		k = j;
		i = 0;
		while (haystack[k] == needle[i] && (j + i) < len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)(haystack + (k - i + 1)));
			k++;
		}
		j++;
	}
	return (NULL);
}

