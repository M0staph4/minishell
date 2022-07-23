#include "../inc/header.h"

void    builtins_pwd(void)
{
    char buf[250];

    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
}

void    builtins_echo(char **arg)
{
    int i;

    i = 1;
    while (arg)
    {
        printf("%s", arg[i]);
        i++;
    }
    if (ft_strncmp(arg[0], "-n"))
    {
    else
    
    printf("%s\n", arg);
}

void    builtins_cd(char *path)
{
    if (path == NULL)
        chdir(getenv("HOME"));
    chdir(path);
}
