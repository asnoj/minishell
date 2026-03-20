/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 00:00:00 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/12 23:23:37 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_is_space(cmd[i]))
			i++;
		if (cmd[i] && !ft_is_space(cmd[i]))
		{
			count++;
			while (cmd[i] && !ft_is_space(cmd[i]))
				i++;
		}
	}
	return (count);
}

char	*get_first_arg(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && !ft_is_space(cmd[i]))
		i++;
	while (cmd[i] && ft_is_space(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	return (&cmd[i]);
}

char	*extract_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && !ft_is_space(str[i]))
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, i + 1);
	return (word);
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}
