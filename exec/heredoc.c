#include "../inc/header.h"
// void    handle_c()
// {
	
// }

// void handler_heredoc_sg()
// {

// }
void heredoc_implementation(char *delim, int end)
{
    char *buff;

    buff = NULL;
    // if (fork() == 0)
    // {
        while((ft_strncmp(delim, buff, ft_strlen(delim))))
        {
            // handler_heredoc_sg();
            buff = readline("> ");
            // if (signal(SIGINT, NULL))
            // {
            //     exit_status = 130;
            //     break;
            // }
            if (!buff)
            {
                free(buff);
                break;
            }
            if ((ft_strncmp(delim, buff, ft_strlen(delim))))
                ft_putendl_fd(buff, end);
            free(buff);
        }
    //     exit(0);
    // }
}

void    heredoc(t_parser **parse)
{
    t_parser *parser;
    t_redirection *red;
    int end[2];
    parser = *parse;
    while (parser)
    {
        red = parser->red; 
        while(red)
        {
            if (red->type == TOKEN_HEREDOC)
            {
                pipe(end);
                heredoc_implementation(red->file, end[WRITE]);
                red->end = end[READ];
                close(end[WRITE]);
            }
            red = red->next;
        }
        parser = parser->next;
    }
} 
