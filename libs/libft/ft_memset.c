#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	int				i;

	temp = b;
	i = 0;
	while (len > 0)
	{
		temp[i] = c;
		len--;
		i++;
	}
	return (b);
}
