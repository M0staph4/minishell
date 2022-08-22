#include "../../inc/header.h"

void    exec_cd(char *path, t_env_list *env)
{
    if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		if (search_env(&env, "HOME"))
			chdir(get_env(&env, "HOME"));
		else
		{
			printf("cd: HOME not set\n");
			exit_code = 1;
		}
	}
	else
	{
		if (chdir(path))
		{
			perror("cd: ");
			exit_code = 1;
		}
	}
}
