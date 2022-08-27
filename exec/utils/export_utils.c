#include "../../inc/header.h"

int	ft_isalnumdash(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (1);
	return (0);
}

size_t	ft_strnchr(const char *s, int c)
{
	size_t	i;
	char	*s1;
	size_t	len;

	s1 = (char *)s;
	len = ft_strlen(s1) + 1;
	i = 0;
	while (i < len)
	{
		if (*s1 == (char)c)
			return (i);
		s1++;
		i++;
	}
	return (0);
}

int	check_doube(t_env_list **env, char *key)
{
	char **tmp;

	tmp  = ft_split(key, '=');
	if (search_env(env, tmp[0]))
		return (1);
	else if (ft_strnchr(tmp[0], '+') == ft_strlen(tmp[0]) - 1)
	{
		tmp[0] = ft_substr(tmp[0], 0, ft_strlen(tmp[0]) -1);
		if (search_env(env, tmp[0]))
			return (2);
	}
	return (0);
}

int	check_key(char *key)
{
    int i;
	char **keys;

    i = 1;
	keys = ft_split(key, '=');
    if (ft_isalpha(keys[0][0]) || keys[0][0] == '_')
    {
        while(keys[0][i])
        {
            if (!ft_isalnumdash(keys[0][i]))
            {
                print_error(": not a valid identifier\n", keys[0], 1);
                return (0);
            }
            i++;
        }
    }
    else
    {
        print_error(": event not found\n", key, 0);
        return (0);
    }
    return (1);
}

t_env_list	*env_last(t_env_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}