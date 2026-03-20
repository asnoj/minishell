/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:43:32 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 19:24:06 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char charset, char c)
{
	if (charset == c)
		return (1);
	return (0);
}

static int	ft_cmpt_word(char *s, char c)
{
	int	i;
	int	nbrword;

	nbrword = 0;
	i = 0;
	while (s[i] && ft_ischarset(c, s[i]))
		i++;
	while (s[i])
	{
		if (!ft_ischarset(s[i], c) && s[i])
		{
			nbrword++;
			while (!ft_ischarset(s[i], c) && s[i])
				i++;
		}
		else
			i++;
	}
	return (nbrword);
}

static void	free_all(char **s, int n)
{
	while (n--)
	{
		free(s[n]);
	}
	free(s);
}

static char	*ft_splitdup(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *s, char c)
{
	int		cmpt;
	int		i;
	char	**strs;

	strs = (char **)malloc((ft_cmpt_word((char *)s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	cmpt = 0;
	while (s[i] && ft_ischarset(c, s[i]))
		i++;
	while (s[i])
	{
		if (!ft_ischarset(s[i], c) && s[i])
		{
			strs[cmpt] = ft_splitdup((char *)&s[i], c);
			if (!strs[cmpt++])
				return (free_all(strs, cmpt), NULL);
			while (!ft_ischarset(s[i], c) && s[i])
				i++;
		}
		else
			i++;
	}
	return (strs[cmpt] = NULL, strs);
}
