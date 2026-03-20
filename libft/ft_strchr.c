/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:34:45 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/16 09:39:19 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char) c)
		i++;
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	else if ((char) c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

//int main()
//{
//	char *str = "patatte";
//	int c = '\0';
//	printf("%s", ft_strchr(str, c));
//}