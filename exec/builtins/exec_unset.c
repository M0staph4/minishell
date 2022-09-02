#include "../../inc/header.h"

void delete_node(t_env_list *current, char *key)
{
    t_env_list    *temp;

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
    t_env_list    *current;
    t_env_list    *temp;
    int            i;

    current = *env;
    i = 1;
    while (key[i])
    {
        if (!key[i])
            return ;
        else if (check_key(key[i]))
        {
            if (!ft_strncmp((*env)->key, key[i], ft_strlen(key[i])))
            {
                    temp = (*env);
                    (*env) = (*env)->next;
                    free(temp->key);
                    free(temp->content);
                    free(temp);
            }
            else
                delete_node(current, key[i]);
        }
        i++;
    }
}