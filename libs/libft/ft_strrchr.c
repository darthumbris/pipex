char	*ft_strrchr(const char *s, int c)
{
	char	*rev;

	rev = (char *)s;
	while (*rev)
		rev++;
	while (c > 256)
		c -= 256;
	while (rev >= s)
	{
		if (*rev == c)
			return (rev);
		rev--;
	}
	if (c == '\0')
		return (rev);
	return (0);
}
