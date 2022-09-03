/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:15:03 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:15:05 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	append_value(t_env_list **env, char *key_a, char *value)
{
	t_env_list	*tmp;
	char		*key;

	tmp = *env;
	key = ft_substr(key_a, 0, ft_strlen(key_a) -1);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
		{
			tmp->separator = "=";
			if (!tmp->content)
				tmp->content = ft_strdup(value);
			else
				tmp->content = ft_strjoin(tmp->content, value);
		}
		tmp = tmp->next;
	}
	free(key);
}

void	replace_value(t_env_list **env, char *key, char *value)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
		{
			tmp->separator = "=";
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(value);
		}
		tmp = tmp->next;
	}
}

void	add_key(t_env_list *env, char *args)
{
	char		**temp;
	t_env_list	*tmp;

	temp = NULL;
	if (ft_strchr(args, '='))
	{
		temp = ft_split(args, '=');
		if (temp[1])
			env_add_back(&env, new_env(temp[0], temp[1], "="));
		else
			env_add_back(&env, new_env(temp[0], NULL, "="));
		free_array(temp);
	}
	else
	{
		tmp = new_env(args, NULL, NULL);
		env_add_back(&env, tmp);
	}
}

void	set_export(t_env_list *env, char **args, int i)
{
	char	**temp;

	temp = NULL;
	while (args[i])
	{
		if (args[i][0] == '=' || args[i][0] == '\0')
			print_error(": not a valid identifier\n", args[i], 1);
		else if (!check_doube(&env, args[i]))
		{
			if (check_key(args[i], 1))
				add_key(env, args[i]);
		}
		else
		{
			temp = ft_split(args[i], '=');
			if (check_doube(&env, args[i]) == 1
				&& (temp[1] || ft_strchr(args[i], '=')))
				replace_value(&env, temp[0], temp[1]);
			else if (check_doube(&env, args[i]) == 2)
				append_value(&env, temp[0], temp[1]);
			free_array(temp);
		}
		i++;
	}
}

void	exec_export(t_parser *parse, t_env_list **envp)
{
	t_env_list	*env;

	env = *envp;
	if (parse->args[1] && parse->args[1][0] != '#')
		set_export(env, parse->args, 1);
	else
	{
		while (env)
		{
			if (!env->separator && !env->content)
				printf("declare -x %s\n", env->key);
			else if (!env->content)
				printf("declare -x %s%s\"\"\n", env->key, env->separator);
			else
				printf("declare -x %s%s\"%s\"\n", env->key,
					env->separator, env->content);
			env = env->next;
		}
	}
}
