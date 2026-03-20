/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:57:30 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/16 22:41:00 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*dest;

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = start;
	while (s1[end])
		end++;
	end--;
	while (end > start && is_set(s1[end], set))
		end--;
	dest = (char *)malloc((end - start + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (start <= end)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}

//int	main(void)
//{
//	char *str = "ffff";
//	char *set = "f";
//	printf("%s", ft_strtrim(str, set));
//}