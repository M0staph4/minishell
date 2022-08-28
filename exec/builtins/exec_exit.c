#include "../../inc/header.h"

int is_numeric(char *ar)
{
    int i;

    i = 0;
    if (ar[0] == '-')
        i++;
    while (ar[i])
    {
        if (ar[i] < '0' || ar[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void    exec_exit(t_parser *parser)
{
     if (!parser->args[1])
     {
        ft_putendl_fd("exit", 1);
        exit(0);
     }
    if (parser->args[2])
    {
        ft_putendl_fd("exit\nexit: too many arguments", 2);
        exit_status = 1;
    }
    else if (!is_numeric(parser->args[1]))
    {
        ft_putendl_fd("exit\nexit: numeric argument required", 2);
        exit_status = 255;
        exit(exit_status);
    }
    else
    {
        exit_status = ft_atoi(parser->args[1]);
        ft_putendl_fd("exit", 1);
        exit(exit_status);
    }
}