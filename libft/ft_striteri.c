/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:46:16 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 10:58:34 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

//void	f(unsigned int i, char *s)
//{
//	if (i % 2 == 0)
//		ft_tolower(s[i]);
//}

//int main()
//{
//	char *str = "abcdefg";
//	ft_striteri(str, f);
//	printf("%s", str);
//}
