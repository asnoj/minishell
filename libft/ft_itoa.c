/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:51:23 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 15:15:40 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nb(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*fill(char *str, long int count, long int n, int signe)
{
	int	c;

	c = 0;
	if (signe == 1)
	{
		str[c] = '-';
		c++;
	}
	while (count != 1)
	{
		str[c] = (n / count) % 10 + '0';
		count = count / 10;
		c++;
	}
	str[c] = n % 10 + '0';
	str[c + 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	count;
	int			c;
	int			signe;
	long int	nb;

	signe = 0;
	count = 1;
	nb = n;
	c = 0;
	if (nb < 0)
	{
		nb = -nb;
		signe = signe + 1;
	}
	c = len_nb(nb);
	str = (char *)malloc((c + 1 + signe) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (c-- > 0)
		count = count * 10;
	str = fill(str, count / 10, nb, signe);
	return (str);
}

//int main()
//{
//	int n = 9788970;
//	char *str = ft_itoa(n);
//	ft_putendl_fd(str, 1);
//	free (str);
//}

//99998998499849998498