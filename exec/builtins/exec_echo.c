#include "../../inc/header.h"

int compare(char *arg)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int check_echo(char *args)
{
    if (args[0] == '-')
    {
        if (compare(args))
            return (1);
    }
    return (0);
}

void print_args(char **args)
{
    int i;

    i = 2;
    while(args[i])
    {
        if (!check_echo(args[i]))
        {
            if (!ft_strncmp(args[i], "$?", 3))
            {
                printf("%d", exit_code);
                exit_code = 0;
            }
            else
                printf("%s", args[i]);
            if (args[i + 1] != '\0')
                printf(" ");
        }
        i++;
    }
}

void print_without_option(char **args)
{
    int i;

    i = 1;
    while(args[i])
    {
        if (!ft_strncmp(args[i], "$?", 3))
        {
            printf("%d", exit_code);
            exit_code = 0;
        }
        else
            printf("%s", args[i]);
        if (args[i + 1] != '\0')
            printf(" ");
        i++;
    }
    printf("\n");
}

void    exec_echo(t_parser *parser)
{
    if (!parser->args[1])
        printf("\n");
    else if (check_echo(parser->args[1]))
        print_args(parser->args);
    else
        print_without_option(parser->args);
}