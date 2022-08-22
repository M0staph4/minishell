#include "../../inc/header.h"

//unset $HME:
//  not enough arguments

// void    delete_env(t_env_list **env,  char *key)
// {
//     t_env_list    *current;
//     t_env_list    *temp;

//     current = (*env);
   
// }

void    exec_unset(t_env_list **env, char *key)
{
    t_env_list    *current;
    t_env_list    *temp;
	int i = 0;

    current = *env;
    if (!key)
        return ;
    else if (check_key(key))
    {
        if (!ft_strncmp((*env)->key, key, ft_strlen(key)))
        {
                temp = (*env);
                (*env) = (*env)->next;
                free(temp);
        }
        else
        {
            while (current->next)
            {
                if (!ft_strncmp(current->next->key, key, ft_strlen(key) + 1))
                {
					i = 1;
                    temp = current->next;
					if (current->next->next)
                    	current->next = current->next->next;
					else 
					{
						current->next = NULL;
						break;
					}
                    free(temp);
                }
                current = current->next;
            }
        }
    }
}