/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:14:21 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:15:23 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	exec_pwd(t_env_list **env)
{
	char	buf[250];

	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		printf("%s\n", get_env(env, "PWD"));
	exit(0);
}
