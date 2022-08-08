  #include "../inc/header.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**find_path(env_list *env)
{
	char	**paths;

	paths = ft_split(find_path_env(env, "PATH="), ':');
	return (paths);
}

char *find_path_env(env_list *env, char *path)
{
	env_list *temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, path, 5))
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}

char	*search(env_list *env, char *cmd)
{
	int		i;
	char	**paths;
	char	*x;
	char	*x2;

	i = 0;
	paths = find_path(env);
	while (paths[i])
	{
		x2 = ft_strjoin(paths[i], "/");
		x = ft_strjoin(x2, cmd);
		free(x2);
		if (access(x, F_OK) == 0)
		{
			free_array(paths);
			return (x);
		}
		free(x);
		i++;
	}
	free_array(paths);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}
