#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*dup;
	const char	*s1_temp;
	size_t		len;

	s1_temp = s1;
	len = ft_strlen(s1_temp);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == 0)
		return (NULL);
	ft_memcpy(dup, s1, len);
	dup[len] = '\0';
	return (dup);
}
