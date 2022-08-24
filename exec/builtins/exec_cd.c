#include "../../inc/header.h"

char	*pwd()
{
	char buf[250];
	char *buff;

	buff = buf;
    getcwd(buf, sizeof(buf));
	buff =ft_strdup(buf);
	return (buff);
}

void    exec_cd(char *path, t_env_list *env)
{
    if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		replace_value(&env, "OLDPWD", pwd());
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
		replace_value(&env, "OLDPWD", pwd());
		if (chdir(path))
		{
			perror("cd: ");
			exit_code = 1;
		}
		replace_value(&env, "PWD", pwd());
	}
}

