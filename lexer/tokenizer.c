#include "../inc/header.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	token->content = ft_strdup(value);
	token->type = type;
	free(value);
	return (token);
}
