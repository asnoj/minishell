/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:52:08 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 10:26:37 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lendest;
	size_t	lensrc;
	size_t	i;

	i = 0;
	lensrc = ft_strlen(src);
	lendest = 0;
	while (lendest < size && dest[lendest])
		lendest++;
	if (lendest == size)
		return (lendest + lensrc);
	while (src[i] && lendest + i + 1 < size)
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}

// int main()
//{
//	char *dest = "bonjour";
//	char *src = "je suis";
//	printf("%s", strlcat(dest, src, 6));
//}