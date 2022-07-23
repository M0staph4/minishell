#include "../inc/header.h"
#include "../inc/parser.h"

t_redirection	*new_red(char *type, char *file)
{
	t_redirection	*new;

	new = malloc(sizeof(t_redirection) * 1);
	if (!new)
		return (0);
	new->type = type;
    new->file = file;
	new->next = NULL;
	return (new);
}


int	red_size(t_redirection *lst)
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

void	red_add_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*list;

	list = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		list = red_last(*lst);
		list->next = new;
	}
}

void	red_add_front(t_redirection **lst, t_redirection *new)
{
	if (new)
		new->next = *lst;
	*lst = new;
}

t_redirection	*red_last(t_redirection *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
