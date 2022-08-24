#include "../../inc/header.h"

void    exec_pwd(t_env_list *env)
{
    char buf[250];

    if (getcwd(buf, sizeof(buf)))
        printf("%s\n", buf);
    else
        printf("%s\n", get_env(&env, "PWD"));
    exit(0);
}