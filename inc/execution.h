#ifndef EXECUTIONS_H
#define EXECUTIONS_H

typedef struct  env_list
{
    char            *key;
    char            *content;
    char            *separator;
    struct env_list *next;    
}   env_list;

//builtins
void    exec_cd(char *path);
void    exec_echo(char **arg);
void    execute_env(env_list *env, char **envp);
void    exec_exit(char *arg);
void    exec_export(env_list *env, char **args);
void    exec_pwd(void);
void    exec_unset(env_list *env, char *key);

//env_list
env_list	*env_last(env_list *lst);
env_list	*new_env(char *key, char *content, char *separator);
void	env_add_back(env_list **lst, env_list *new);
env_list    **read_env(char **envp);


//export
void	set_export(env_list *env,  char *line);
void	replace_value(env_list  *env, char *key, char *value);
void    print_export(env_list *env);


//unset
int     check_key(env_list **env, char *key);
void    delete_env(env_list **env,  char *key);


void	execute(t_parser **parse);

#endif