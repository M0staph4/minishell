#include "../inc/header.h"

t_parser	*new_parse(char *cmd , char **args , t_redirection *redirection)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->cmd = ft_strdup(cmd);
    new->args = args;
	new->red = redirection;
	new->next = NULL;
	return (new); 
}

int	parse_size(t_parser *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}


void	parser_add_back(t_parser **alst, t_parser *new)
{
	t_parser	*n;

	n = *alst;
	if (!new)
		return ;
	if (!*alst)
		(*alst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
}

void	parser_add_front(t_parser **lst, t_parser *new)
{
	if (new)
		new->next = *lst;
	*lst = new;
}

t_parser	*parser_last(t_parser **lst)
{
	int	i;

	i = 0;
	if (!*lst)
		return (0);
	while ((*lst)->next)
		*lst = (*lst)->next;
	return (*lst);
}