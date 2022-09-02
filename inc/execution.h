#ifndef EXECUTIONS_H
#define EXECUTIONS_H

#define WRITE 1
#define  READ 0


//builtins
void    exec_cd(char *path, t_env_list **env);
void    exec_echo(t_parser *parser);
void    exec_env(t_parser *parse, t_env_list **envp);
void    exec_exit(t_parser *parser);
void    exec_export(t_parser *parse, t_env_list **envp);
void    exec_pwd(t_env_list **env);
void    exec_unset(t_env_list **env, char **key);

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
int     check_doube(t_env_list **env, char *key);
void	add_key(t_env_list *env,  char *args);


//unset
void    delete_env(t_env_list **env,  char *key);
int     ft_count_elems(char **str);


void 	exec_builtins(t_parser *parser, t_env_list **env);
void    pipeline_execution(t_parser **parser, t_env_list **envp);
int     redirections(t_redirection *red, char *cmd);


char	*search(char **env, char *cmd);
char	**find_path(char **envp);
int	    find_path_env(char **envp, char *path);
void	free_array(char **array);
void     heredoc(t_parser **parse);


void	dup_end(int end, int dup_fd);
void	close_pipe(int *end, int fd_in);
int    redirection_out_to(t_redirection *red);
void    print_error(char *error, char *ar, int ex_code);
int		check_builtin(t_parser *parser);
int parent_builtins(t_parser *parser);
int print_error2(char *error, char *ar, int ex_code);
char	*join_env(char const *s1, char const *s2);
void    dup_redirections(int input, int output, char *cmd);

void hd_sg();
void    handler();

#endif