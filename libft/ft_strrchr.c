/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:11:05 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/03 23:20:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_ocur;

	i = 0;
	last_ocur = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			last_ocur = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (last_ocur);
}

// int main()
//{
//	char *str = "";
//	int c = 'o';
//	printf("%s", strrchr(str, c));
// }