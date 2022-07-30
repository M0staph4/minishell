#include "../../inc/header.h"

void    builtins_echo(char **arg)
{
    int i;

    i = 1;
    while (arg)
    {
        printf("%s ", arg[i]);
        i++;
    }
    if (ft_strncmp(arg[0], "-n", 2))
        printf("\n");
        //variables
}