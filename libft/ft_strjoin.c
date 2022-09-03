/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:12:51 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/03 02:56:59 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

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
	free(s1);
	return (result);
}
