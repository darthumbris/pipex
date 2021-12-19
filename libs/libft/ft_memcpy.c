#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src_str;
	char		*dst_str;

	src_str = src;
	dst_str = dst;
	if (src == NULL && dst == NULL)
		return (dst);
	while (n)
	{
		*dst_str = *src_str;
		dst_str++;
		src_str++;
		n--;
	}
	return (dst);
}
