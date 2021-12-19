int	ft_atoi(const char *str)
{
	long int	nbr;
	int			min;

	nbr = 0;
	min = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * min);
}
