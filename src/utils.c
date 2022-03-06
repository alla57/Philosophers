#include "../include/philosophers.h"

int	is_even(int nb)
{
	return !(nb % 2);
}

int	is_bigger_than_intmax(char *num)
{
	int i;

	i = 0;
	while (*num && *num == '0')
		++num;
	while (num[i] && num[i] >= '0' && num[i] <= '9')
		++i;
	if (i > 10)
		return (1);
	if (ft_atoi(num) < 0)
		return (1);
	return (0);
}

int	is_valid_number(char *num)
{
	int	i;

	i = 0;
	if (is_bigger_than_intmax(num))
		return (0);
	while (num[i] && num[i] >= '0' && num[i] <= '9')
		++i;
	if (i && !num[i])
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	n;

	n = 0;
	while (*s && *s >= '0' && *s <= '9')
	{
		n = 10 * n + (*s - '0');
		s++;
	}
	return (n);
}
