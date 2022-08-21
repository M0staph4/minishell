/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:04:34 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/14 22:01:07 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (1);
	while (i < n)
	{
		if (s11[i] && s22[i] && s11[i] == s22[i])
		{
			i++;
			continue ;
		}
		return (s11[i] - s22[i]);
	}
	return (0);
}
