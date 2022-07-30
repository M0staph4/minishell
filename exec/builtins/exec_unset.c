#include "../../inc/header.h"

int     check_key(env_list **env, char *key)
{
    env_list    *temp;

    temp = (*env);
    while (temp)
    {
        if (!ft_strncmp(temp->key, key, ft_strlen(key)))
            return (0);
        temp = temp->next
    }
    return (1);
}

void    delete_env(env_list **env,  char *key)
{
    env_list    *current;
    env_list    *temp;
    int i = 0;

    current = (*env);
    if (!ft_strncmp((*env)->key, key, ft_strlen(key)))
    {
            temp = *env;
            env= env->next;
            free(temp);
    }
    else
    {
        while (current->next)
        {
            if (!ft_strncmp(current->next->key, key, ft_strlen(key)))
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
            }
            current = current->next;
        }
    }
}

void    exec_unset(env_list *env, char *key)
{
    if (!check_key(env, key))
        delete_env(env, key);
    else
        printf("\n");
}