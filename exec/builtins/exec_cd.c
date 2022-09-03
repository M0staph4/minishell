/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:14:30 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:14:33 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char	*get_pwd(void)
{
	char	buf[250];
	char	*buff;

	buff = buf;
	if (getcwd(buf, sizeof(buf)))
		buff = ft_strdup(buf);
	else
		buff = NULL;
	return (buff);
}

void	replace_pwd(t_env_list **env, char *old_pwd)
{
	char	*pwd;

	pwd = get_pwd();
	if (search_env(env, "OLDPWD"))
	{
		if (old_pwd)
			replace_value(env, "OLDPWD", old_pwd);
		else
			replace_value(env, "OLDPWD", get_env(env, "PWD"));
	}
	replace_value(env, "PWD", pwd);
	free(pwd);
}

void	cd_home(t_env_list **env, char *old_pwd)
{
	if (search_env(env, "HOME"))
	{
		chdir(get_env(env, "HOME"));
		replace_pwd(env, old_pwd);
	}
	else
		print_error("cd: HOME not set\n", NULL, 1);
}

void	exec_cd(char *path, t_env_list **env)
{
	char	*old_pwd;

	old_pwd = get_pwd();
	if (path == NULL || !ft_strncmp(path, "~", 2))
		cd_home(env, old_pwd);
	else
	{
		if (path[0] == '\0')
		{
			free(old_pwd);
			return ;
		}
		else if (chdir(path))
			print_error2(": No such file or directory", path, 1);
		else
			replace_pwd(env, old_pwd);
	}
	free(old_pwd);
}
