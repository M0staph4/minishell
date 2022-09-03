/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:14:47 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:14:49 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*join_env(char const *s1, char const *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (0);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result)
		ft_strcat(ft_strcpy(result, s1), s2);
	return (result);
}

char	**t_env_list_to_char(t_env_list **env)
{
	t_env_list	*tmp;
	char		**envp;
	int			i;

	envp = malloc (sizeof(char *) * (env_size(env) + 1));
	tmp = (*env);
	i = 0;
	while (tmp)
	{
		envp[i] = join_env(tmp->key, tmp->separator);
		envp[i] = join_env(envp[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

t_env_list	*env_builder(char **envp)
{
	char		**tmp;
	int			i;
	t_env_list	*env;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		env_add_back(&env, new_env(tmp[0], tmp[1], "="));
		free_array(tmp);
		i++;
	}
	return (env);
}

void	exec_env(t_parser *parse, t_env_list **envp)
{
	t_env_list	*env;

	env = *envp;
	if (parse->args[1])
	{
		print_error2(": No such file or directory", parse->args[1], 127);
		return ;
	}
	while (env)
	{
		if (env->separator)
		{
			printf("%s%s", env->key, env->separator);
			if (env->content)
				printf("%s", env->content);
			printf("\n");
		}
		env = env->next;
	}
}
