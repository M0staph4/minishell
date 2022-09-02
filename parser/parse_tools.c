#include "../inc/header.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

char	**add_args_to_list(char **args, t_token *token)
{
	char	**new_args;
	int		i;
	int		count;

	count = count_args(args);
	i = -1;
	new_args = malloc (sizeof(char *) * (count + 2));
	while (++i < count)
		new_args[i] = args[i];
	if (count)
		free(args);
	new_args[i++] = ft_strdup(token->content);
	new_args[i] = NULL;
	free(token->content);
	return (new_args);
}
