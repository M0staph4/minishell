#include "../inc/header.h"

void    redirection_in_from(t_redirection *red)
{
    int input;

    input = open(red->file, O_RDONLY, 0777);
    dup2(input, STDOUT_FILENO);
    close(input);
    //handle errors
}

void    redirection_out_to(t_redirection *red)
{
    int output;

    if (red->type == REDOUT)
    {
        output = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(output, STDOUT_FILENO);
        close(output);
    }
    else if (red->type == APPEND)
    {
        output = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        dup2(output, STDOUT_FILENO);
        close(output);
    }
    //handle errors
}
