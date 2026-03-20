/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:07:21 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 19:23:54 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*c;
	unsigned char		*cpy;

	c = (const unsigned char *) src;
	cpy = (unsigned char *) dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n--)
			cpy[n] = c[n];
	}
	return (dest);
}
