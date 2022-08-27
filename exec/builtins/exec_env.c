#include "../../inc/header.h"

char **t_env_list_to_char(t_env_list **env)
{
	t_env_list *tmp;
	char **envp = malloc (sizeof(char *) * (env_size(env) + 1));
	int i;

	tmp = (*env);
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, tmp->separator);
		envp[i] = ft_strjoin(envp[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

t_env_list    *env_builder(char **envp)
{
    char        **tmp;
    int         i;
	t_env_list	*env;

	env  = NULL;
    i = 0;
    while(envp[i])
    {
        tmp = ft_split(envp[i], '=');
        env_add_back(&env, new_env(tmp[0], tmp[1], "="));
		i++;
    }
	return (env);
}

void exec_env(t_parser *parse, t_env_list **envp)
{
	t_env_list	*env;

	env = *envp;
	if (parse->args[1])
	{
		printf("env: %s: No such file or directory\n", parse->args[1]);
		return ;
	}
	while (env)
	{
		if (env->separator && env->content)
			printf("%s%s%s\n", env->key, env->separator, env->content);
		env = env->next;
	}
}
