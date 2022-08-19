#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	i;
	char	*p;

	if (s2 == NULL)
		return ((char *)s1);
	if (s1 == NULL && s2 != NULL)
		return ((char *)s2);
	i = ft_strlen (s1);
	j = ft_strlen (s2);
	p = malloc(i + j + 1);
	if (p == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i] != '\0')
		p[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}
