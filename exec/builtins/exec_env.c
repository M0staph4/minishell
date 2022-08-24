#include "../../inc/header.h"

char *get_env(t_env_list  **env, char *key)
{
    t_env_list *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
            return (tmp->content);
        tmp = tmp->next;
    }
	return (NULL);
}

int    search_env(t_env_list  **env, char *key)
{
    t_env_list *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
            return (1);
        tmp = tmp->next;
    }
	return (0);
}

int	env_size(t_env_list **env)
{
	int	size;
	t_env_list *lst;

	lst = (*env);
	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

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

t_env_list	*new_env(char *key, char *content, char *separator)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list) * 1);
	if (!new)
		return (0);
	new->key = key;
    new->content = content;
	new->separator = separator;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*n;

	n = *lst;
	if (!new)
		return ;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
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
