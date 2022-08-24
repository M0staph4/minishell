#include "../inc/header.h"

int heredoc_implementation(char *delim)
{
    char *buff;
    int end[2];

    buff = NULL;
    pipe(end);
    while((ft_strncmp(delim, buff, ft_strlen(delim))))
    {
        buff = readline("heredoc> ");
        if ((ft_strncmp(delim, buff, ft_strlen(delim))))
            ft_putendl_fd(buff, end[WRITE]);
    }
                close(end[WRITE]);

    return (end[READ]);
}
int    heredoc(t_parser **parse)
{
    t_parser *parser;
    t_redirection *red;
    int             end;

    parser = *parse;
    while (parser)
    {
        red = parser->red; 
        while(red)
        {
            if (red->type == TOKEN_HEREDOC)
               end =  heredoc_implementation(red->file);
            red = red->next;
        }
        parser = parser->next;
    }
	return (end);
} 
