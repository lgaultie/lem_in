// Header 42

#include "libft.h"

/*
** ft_isnumber() checks that the string is between INT_MIN and INT_MAX.
*/

int	ft_isnumber(char *number)
{
	int		i;
	int 	len;
	long	tmp;

	i = 0;
	len = 0;
	if (number[i] == ' ')
		i++;
	if (number[i] == '-' || number[i] == '+')
		i++;
	if (number[i] == '0')
		i++;
	while (number[i])
	{
		if (!ft_isdigit(number[i]))
			return (0);
		i++;
		len++;
		if (len > 10)
			return (0);
	}
	tmp = ft_atoi_long(number);
	if ((tmp < INT_MIN) || (tmp > INT_MAX))
		return (0);
	return (1);
}