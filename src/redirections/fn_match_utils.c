/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_match_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:10:13 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 00:08:36 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_range(char *pattern, char *str, int i, int j)
{
	int	add;

	add = 0;
	if (pattern[i + 2] - pattern[i] < 0)
		return (1);
	while (pattern[i] + add != pattern[i + 2]
		&& pattern[i] + add != str[j])
		add++;
	return (0);
}

int	match_set(char *pattern, char *str, int i, int j)
{
	(void)j;
	while (pattern[i] && pattern[i] != str[j])
		i++;
	if (pattern[i] == '\0')
		return (1);
	return (0);
}

int	skip_to_bracket(char *pattern, int i)
{
	while (pattern[i] && pattern[i] != ']')
		i++;
	return (i);
}

int	fnmatch_crochet(char *pattern, char *str, int i, int j)
{
	int	signe;

	signe = 0;
	i++;
	if (pattern[i + 1] == '!')
	{
		signe = 1;
		i++;
	}
	if (pattern[i + 1] == '-')
	{
		if (match_range(pattern, str, i, j))
			return (1);
	}
	else if (match_set(pattern, str, i, j))
		return (1);
	if (pattern[i] == str[j] && signe == 1)
		return (1);
	i = skip_to_bracket(pattern, i);
	if (pattern[i] == '\0')
		return (1);
	return (ft_fnmatch(pattern, str, i + 1, j + 1));
}
