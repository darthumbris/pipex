#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_str;
	const unsigned char	*s2_str;

	s1_str = s1;
	s2_str = s2;
	while (n)
	{
		n--;
		if (*s1_str != *s2_str)
			return (*s1_str - *s2_str);
		s1_str++;
		s2_str++;
	}
	return (0);
}
