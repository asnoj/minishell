/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:03:38 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/21 18:19:04 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*c;
	unsigned char		*cpy;
	unsigned int		i;

	c = (const unsigned char *) src;
	cpy = (unsigned char *) dest;
	i = 0;
	if (!src && !dest)
		return (NULL);
	while (n > i)
	{
		cpy[i] = c[i];
		i++;
	}
	return (dest);
}

//int main()
//{
//	char *str;
//	char *st;
//	int i = 0;

//	str = malloc(90);
//	st = malloc(500);
//	while (i < 5)
//		str[i++] = 's';
//	i = 0;
//	while (i < 10)
//		st[i++] = 'l';
//	st = ft_memcpy(st, str, 20);
//	printf("%s",st);
//	i = 0;
//}