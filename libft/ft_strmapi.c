/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:16:21 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 10:04:24 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		l;
	char	*new;
	int		i;

	l = ft_strlen(s);
	i = 0;
	new = malloc((l + 1));
	if (!new)
		return (NULL);
	while (i < l)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

//char	*f(unsigned int i, char c)
//{
//	return (c);
//}

//int main()
//{
//	char *s = "abc";
//	char *str;
//	str = ft_strmapi(s, f);
//	printf("%s", str);
//	free (str);
//}