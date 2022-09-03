/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:23:07 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:23:09 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	print_error(char *error, char *ar, int ex_code)
{
	ft_putstr_fd(ar, 2);
	ft_putstr_fd(error, 2);
	exit_status = ex_code;
}

int	print_error2(char *error, char *ar, int ex_code)
{
	ft_putstr_fd(ar, 2);
	ft_putendl_fd(error, 2);
	exit_status = ex_code;
	return (exit_status);
}
