#include "../../inc/header.h"

void delete_node(t_env_list **env, char *key)
{
    t_env_list    *temp;
    t_env_list    *current;

    current = *env;
    while (current->next)
    {
        if (!ft_strncmp(current->next->key, key, ft_strlen(key) + 1))
        {
            temp = current->next;
			if (current->next->next)
            	current->next = current->next->next;
			else 
			{
				current->next = NULL;
                free(temp->key);
                free(temp->content);
                free(temp);
				break;
			}
            free(temp->key);
            free(temp->content);
            free(temp);
        }
        current = current->next;
    }
}

void    exec_unset(t_env_list **env, char **key)
{
    // t_env_list    *current;
    t_env_list    *temp;
    int            i;

    // temp = *env;
    i = 1;
    if (!ft_strncmp((*env)->key, key[i], ft_strlen(key[i])))
    {
        temp = (*env);
        (*env) = (*env)->next;
        temp->next = NULL;
        free(temp->key);
        free(temp->content);
        free(temp);
    }
    while (key[i])
    {
        if (!key[i])
            return ;
        else if (check_key(key[i]))
        {
            delete_node(env, key[i]);
        }
        i++;
    }
}