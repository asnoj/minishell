/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:17:34 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 10:26:20 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*d;
	unsigned int	i;

	i = 0;
	d = (unsigned char *)str;
	while (n > i)
	{
		d[i] = (unsigned char)c;
		i++;
	}
	return (d);
}

//int main()
//{
//	char *str;
//	int c = '#';
//	int i = 0;

//	str = malloc(9000);
//	while (i < 30)
//		str[i++] = 's';
//	ft_memset(str, c, 7);
//	printf("%s",str);
//}