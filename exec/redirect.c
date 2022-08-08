#include "../inc/header.h"

int    redirection_in_from(t_redirection *red)
{
	if (mode == 1 && access(file, F_OK) == 0)
		return (open(red->file, O_RDONLY, 0777));
	else
	{
        perror("file");
		return (-1);
	}
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
}
