#ifndef EXECUTIONS_H
#define EXECUTIONS_H

#define WRITE 1
#define  READ 0


//builtins
void    exec_cd(char *path, t_env_list *env);
void    exec_echo(t_parser *parser);
void    exec_env(t_parser *parse, t_env_list **envp);
void    exec_exit(t_parser *parser);
void    exec_export(t_parser *parse, t_env_list **envp);
void    exec_pwd(t_env_list *env);
void    exec_unset(t_env_list **env, char *key);

//t_env_list
t_env_list	*env_last(t_env_list *lst);
void	    env_add_back(t_env_list **lst, t_env_list *new);
t_env_list    **read_env(char **envp);
t_env_list	*new_env(char *key, char *content, char *separator);
char        **t_env_list_to_char(t_env_list **env);
int         env_size(t_env_list **env);
t_env_list    *env_builder(char **envp);
int         search_env(t_env_list  **env, char *key);
char        *get_env(t_env_list  **env, char *key);

//export
void    set_export(t_env_list *env,  char **args);
void	replace_value(t_env_list  **env, char *key, char *value);
void    print_export(t_env_list **env);
int     check_key(char *key);


//unset
void    delete_env(t_env_list **env,  char *key);
int     ft_count_elems(char **str);


void 	exec_builtins(t_parser *parser, t_env_list *env);
void    pipeline_execution(t_parser *parser, t_env_list **envp, int file);
int     redirections(t_redirection *red, char *cmd, int file);


char	*search(char **env, char *cmd);
char	**find_path(char **envp);
int	    find_path_env(char **envp, char *path);
void	free_array(char **array);
int     heredoc(t_parser **parse);

#endif