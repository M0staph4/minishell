#include "../inc/header.h"

void    redirections(int red, char **arg)
{
    int fd;

    if (red == 1)
    {
        fd = open(arg[3], O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        execvp(arg[1], arg);
    }
    else if (red == 2)
    {
        fd = open(arg[4], O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execvp(arg[1], arg);
    }
}

