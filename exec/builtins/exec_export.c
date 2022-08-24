#include "../../inc/header.h"

int	ft_isalnumdash(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (1);
	return (0);
}

size_t	ft_strnchr(const char *s, int c)
{
	size_t	i;
	char	*s1;
	size_t	len;

	s1 = (char *)s;
	len = ft_strlen(s1) + 1;
	i = 0;
	while (i < len)
	{
		if (*s1 == (char)c)
			return (i);
		s1++;
		i++;
	}
	return (0);
}

int	check_doube(t_env_list **env, char *key)
{
	char **tmp;

	tmp  = ft_split(key, '=');
	if (search_env(env, tmp[0]))
		return (1);
	else if (ft_strnchr(tmp[0], '+') == ft_strlen(tmp[0]) - 1)
	{
		tmp[0] = ft_substr(tmp[0], 0, ft_strlen(tmp[0]) -1);
		if (search_env(env, tmp[0]))
			return (2);
	}
	return (0);
}

int	check_key(char *key)
{
    int i;
	char **keys;

    i = 1;
	keys = ft_split(key, '=');
    if (ft_isalpha(keys[0][0]) || keys[0][0] == '_')
    {
        while(keys[0][i])
        {
            if (!ft_isalnumdash(keys[0][i]))
            {
                printf("export: %s: not a valid identifier\n", keys[0]);
				exit_code = 1;
                return (0);
            }
            i++;
        }
    }
    else
    {
        printf("export: %s: event not found\n", key);
		exit_code = 0;
        return (0);
    }
    return (1);
}

t_env_list	*env_last(t_env_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

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

void set_export(t_env_list *env,  char **args)
{
    char    **temp = NULL;
    int i;
    t_env_list *tmp;
    i = 1;
    while(args[i])
    {
		if (!check_doube(&env, args[i]))
		{
        	if (check_key(args[i]))
        	{
        	    if (ft_strchr(args[i], '='))
        	    {
        	        temp = ft_split(args[i], '=');
        	        if (temp[1])
        	            env_add_back(&env, new_env(temp[0], temp[1], "="));
        	        else
        	            env_add_back(&env, new_env(temp[0], NULL, "="));
        	    }
        	    else
        	    {
        	        tmp = new_env(args[i], NULL, NULL);
        	        env_add_back(&env, tmp);
        	    }  
        		free(temp);
        	}
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