/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 08:38:03 by aronnet           #+#    #+#             */
/*   Updated: 2026/01/26 23:13:54 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//int	ft_strncmp(const char *s1, const char *s2, size_t n)
//{
//	unsigned int		i;
//	unsigned char		*str1;
//	unsigned char		*str2;

//	str1 = (unsigned char *) s1;
//	str2 = (unsigned char *) s2;
//	i = 0;
//	if (n == 0)
//		return (0);
//	while (n - 1 > i && (str1[i] || str2[i]))
//	{
//		if (str1[i] - str2[i] != 0)
//			return (str1[i] - str2[i]);
//		i++;
//	}
//	return (str1[i] - str2[i]);
//}

//int main()
//{
//	char test1[100] = "0123456789";
//	char test2[100] = "0123456789";

//	test1[10] = -2;
//	test2[10] = -1;
//	printf("%d", strncmp(test1, test2, 199));
//	return(0);
//}