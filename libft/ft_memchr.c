/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 08:48:11 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/15 21:48:23 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*str;

	i = 0;
	str = (const unsigned char *) s;
	while (n > i)
	{
		if (str[i] == (unsigned char) c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

//int main()
//{
//	char *str = "gros caca";
//	int c = 'c';
//	char *sr = ft_memchr(str, c, 6);
//	printf("%s", sr);
//}