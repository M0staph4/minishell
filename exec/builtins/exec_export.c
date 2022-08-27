#include "../../inc/header.h"

void append_value(t_env_list  **env, char *key, char *value)
{
	t_env_list *tmp;

    tmp = *env;
	key = ft_substr(key, 0, ft_strlen(key) -1);
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
		{
			tmp->separator = "=";
			if (!tmp->content)
				tmp->content = value;
			else
            	tmp->content = ft_strjoin(tmp->content, value);
		}
        tmp = tmp->next;
    }
}

void    replace_value(t_env_list  **env, char *key, char *value)
{
    t_env_list *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
		{
			tmp->separator = "=";
            tmp->content = value;
		}
        tmp = tmp->next;
    }
}

void	add_key(t_env_list *env,  char *args)
{
	char    **temp;
	t_env_list *tmp;

	temp = NULL;
	if (ft_strchr(args, '='))
    {
        temp = ft_split(args, '=');
        if (temp[1])
            env_add_back(&env, new_env(temp[0], temp[1], "="));
        else
            env_add_back(&env, new_env(temp[0], NULL, "="));
    }
    else
    {
        tmp = new_env(args, NULL, NULL);
        env_add_back(&env, tmp);
    }  
    free(temp);
}

void set_export(t_env_list *env,  char **args)
{
    char    **temp;
    int i;

	temp = NULL;
    i = 1;
    while(args[i])
    {
		if (!check_doube(&env, args[i]))
		{
        	if (check_key(args[i]))
				add_key(env, args[i]);
		}
		else
		{
			temp = ft_split(args[i], '=');
			if (check_doube(&env, args[i]) == 1)
				replace_value(&env, temp[0], temp[1]);
			else if (check_doube(&env, args[i]) == 2)
				append_value(&env, temp[0], temp[1]);
		}
        i++;
    }
}

void exec_export(t_parser *parse, t_env_list **envp)
{
	t_env_list	*env;

	env = *envp;
	if (parse->args[1])
        set_export(env, parse->args);
	else
	{
		while (env)
		{
            if (!env->separator && !env->content)
		        printf("declare -x %s\n", env->key);
            else if (!env->content)
		        printf("declare -x %s%s\"\"\n", env->key, env->separator);
            else
		        printf("declare -x %s%s\"%s\"\n", env->key, env->separator, env->content);
			env = env->next;
		}
	}
}