/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:58:18 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 17:58:21 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_sint(int n)
{
	int	x;

	x = 0;
	if (n < 0)
	{
		x++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		x;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	x = ft_sint(n) + 1;
	if (n == 0)
		return (ft_strdup("0"));
	p = malloc(x);
	if (p == NULL)
		return (NULL);
	if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	p[x - 1] = '\0';
	while (n > 0)
	{
		p[x - 2] = n % 10 + '0';
		n /= 10;
		x--;
	}
	return (p);
}
