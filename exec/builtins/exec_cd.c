#include "../../inc/header.h"

int    exec_cd(char *path, t_env_list *env)
{
	
    if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		if (search_env(&env, "HOME"))
		{
        	if(chdir(get_env(&env, "HOME")))
			{
				printf("cd: HOME not set\n");
				exit_code = 1;
			}
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
	return (0);
}
