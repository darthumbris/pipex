#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	int		i;

	i = 0;
	temp = malloc(count * size);
	if (temp)
		ft_bzero(temp, count * size);
	return (temp);
}
