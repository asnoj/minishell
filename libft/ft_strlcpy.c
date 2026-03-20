/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:31:27 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/15 15:29:58 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return ((size_t)ft_strlen((char *) src));
}

//int main()
//{
//	char *dst;
//	char *src = "caca proute";
//	int i = 0;

//	dst = malloc(4);
//	while (i < 4)
//	{
//		dst[i] = 'p';
//		i++;
//	}

//	printf("%d,%s", ft_strlcpy(dst, src, 5),dst);
//}