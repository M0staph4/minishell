#ifndef EXECUTIONS_H
#define EXECUTIONS_H

typedef struct  env_list
{
    char            *key;
    char            *content;
    char            *separator;
    char            **envp;  
    struct env_list *next;    
}   env_list;

//builtins
void    exec_cd(char *path);
void    exec_echo(char **arg);
void    exec_env(env_list *env, char **envp);
void    exec_exit(char *arg);
void    exec_export(env_list *env, char **args);
void    exec_pwd(void);
void    exec_unset(env_list *env, char *key);

//env_list
env_list	*env_last(env_list *lst);
void	    env_add_back(env_list **lst, env_list *new);
env_list    **read_env(char **envp);
env_list	*new_env(char *key, char *content, char *separator, char **envp);
void 	    ft_get_env(env_list *env, char **envp);


//export
void	set_export(env_list *env,  char *line);
void	replace_value(env_list  *env, char *key, char *value);
void    print_export(env_list *env);


//unset
int     check_key(env_list **env, char *key);
void    delete_env(env_list **env,  char *key);
int ft_count_elems(char **str);


void	exec_builtins(t_parser **parse);

#endif