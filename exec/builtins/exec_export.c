#include "../../inc/header.h"

void set_export(env_list *env,  char *line)
{
    char    *tmp;
    
    if (!check_key(line))
    {
        if (!ft_strchr(line, '='))
        {
            tmp = ft_split(line, '=');
            if (!tmp[1])
                env_add_back(&env, new_env(tmp[0], tmp[1], "="));
            else
                env_add_back(&env, new_env(tmp[0], NULL, "="));
        }
        else
            env_add_back(&env, new_env(tmp[0], NULL, NULL));
        }
    else
        printf("key should start with an alphabet and contain alphanumerics in the middle\n")
}

void    replace_value(env_list  *env, char *key, char *value)
{
    env_list *tmp;

    tmp = (*env);
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
            tmp->content = value;
        tmp = tmp->next;
    }
}

//add str to value
void    print_export(env_list *env)
{
	env_list *list;

	list = env;
	while (!list)
	{
        if (!list->separator)
		    printf("declare -x %s\n", list->key);
        else if (!list->content)
		    printf("declare -x %s%s\n", list->key, list->separator);
        else
		    printf("declare -x %s%s%s\n", list->key, list->separator, list->content);
		list = list->next;
	}
}

void    exec_export(env_list *env, char **args)
{
    while (*args)
        i++;
    if (i <= 1)
        print_export(env);
    else
        set_env(env, args);
}