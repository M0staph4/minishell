#include "../inc/header.h"
int isDir(char *file_name)
{
   struct stat path_stat;
    stat(file_name, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int    redirection_in_from(t_redirection *red)
{
	if (access(red->file, F_OK) == 0)
		return (open(red->file, O_RDONLY, 0777));
	else
		return (-1);
}

int    redirection_out_to(t_redirection *red)
{
    int output = 0;

    if (!red->file)
    {
        perror("File");
        return (-1);
    }
    if (red->file)
    {
        if (red->type == TOKEN_REDOUT)
            output = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        else if (red->type == TOKEN_APPEND)
            output = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (!isDir(red->file))
        {
            ft_putstr_fd(red->file, 2);
            ft_putendl_fd(": Is a directory", 2);
            return (-1);
        }
        return (output);
    }
    return (-1);
}

void    dup_redirections(int input, int output)
{
     if (output != -3)
    {
        dup2(output, STDOUT_FILENO);
        close(output);
    }
    if (input != -2)
    {
        dup2(input, STDIN_FILENO);
        close(input);
    }
}

int    redirections(t_redirection *red, char *cmd, int file)
{
    int output = -3;
    int input = -2;

    if (!red)
        return (0);
    while (red)
    {
        if (red->type == TOKEN_REDIN)
        {
            input = redirection_in_from(red);
            if (input == -1)
            {
                perror("file");
                return (-1);
            }
        }
        else if (red->type == TOKEN_HEREDOC)
            input = file;
        else if (red->type == TOKEN_APPEND || red->type == TOKEN_REDOUT)
        {
            output = redirection_out_to(red);
            if (output == -1)
                return (-1);
        }
        if  (!red->next || !cmd)
            dup_redirections(input, output);
        red = red->next;
    }
    return (0);
}
