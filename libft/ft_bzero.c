/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:30:39 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 10:24:57 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, int n)
{
	unsigned char	*c;
	int				i;

	i = 0;
	c = (unsigned char *) s;
	while (n > i)
	{
		c[i] = '\0';
		i++;
	}
}

//int main()
//{
//	char *str;
//	int i = 0;

//	str = malloc(9000);
//	while (i < 30)
//		str[i++] = 's';
//	ft_bzero(str, 7);
//	printf("%s",str);
//	free(str);
//}