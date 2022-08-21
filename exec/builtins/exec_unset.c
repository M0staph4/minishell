#include "../../inc/header.h"

//unset $HME:
//  not enough arguments

// void    delete_env(t_env_list **env,  char *key)
// {
//     t_env_list    *current;
//     t_env_list    *temp;

//     current = (*env);
   
// }

void    exec_unset(t_env_list **env, t_parser *parser)
{
    t_env_list    *current;
    t_env_list    *temp;
	int i = 1;

    current = *env;
    if (!parser->args[i])
        return ;
    while (parser->args[i])
    {
        if (check_key(parser->args[i]))
        {
            if (!ft_strncmp((*env)->key, parser->args[i], ft_strlen(parser->args[i])))
            {
                    temp = (*env);
                    (*env) = (*env)->next;
                    free(temp);
            }
            else
            {
                while (current->next)
                {
                    if (!ft_strncmp(current->next->key, parser->args[i], ft_strlen(parser->args[i]) + 1))
                    {
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
        i++;
    }
}