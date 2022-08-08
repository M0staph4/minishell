/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:02:13 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/08/08 10:03:28 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if(!s1)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	dst = (char *)malloc(i + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		dst[j] = s1[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
