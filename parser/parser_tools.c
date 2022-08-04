#include "../inc/header.h"
#include "../inc/parser.h"

t_parser	*new_parse(char **args, t_redirection *red)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->cmd = args[0];
    new->args = args;
	new->red = red;
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

void	parser_add_back(t_parser **lst, t_parser *new)
{
	t_parser	*list;

	list = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		list = parser_last(lst);
		list->next = new;
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