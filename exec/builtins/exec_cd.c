#include "../../inc/header.h"

char	*pwd()
{
	char buf[250];
	char *buff;

	buff = buf;
    if(getcwd(buf, sizeof(buf)))
		buff = ft_strdup(buf);
	else
		buff = NULL;
	return (buff);
}

void	replace_pwd(t_env_list *env, char *old_pwd)
{
	if (old_pwd)
		replace_value(&env, "OLDPWD", old_pwd);
	else
		replace_value(&env, "OLDPWD", get_env(&env, "PWD"));
	replace_value(&env, "PWD", pwd());
}

void    exec_cd(char *path, t_env_list *env)
{
	char *old_pwd;

	old_pwd = pwd();
    if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		if (search_env(&env, "HOME"))
		{
			chdir(get_env(&env, "HOME"));
			replace_pwd(env, old_pwd);
		}
		else
		{
			perror("cd: HOME not set");
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
		else
			replace_pwd(env, old_pwd);
	}
}
