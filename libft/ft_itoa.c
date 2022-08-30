/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:34:31 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/08/30 15:53:41 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	countlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*cnvrt(char *str, int len, long n, int i)
{
	while (n > 0 && len != i)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{	
	int		len;
	char	*str;
	int		i;
	long	ng;

	i = 0;
	ng = (long)n;
	len = countlen(ng);
	if (!n)
		return (ft_strdup("0"));
	if (n < 0)
		len++;
	str = (char *)malloc (sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	if (n < 0)
	{
		ng *= -1;
		str[i] = '-';
		i++;
	}
	str = cnvrt(str, len, ng, i);
	str[len] = '\0';
	return (str);
}

