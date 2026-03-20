/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:32:24 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/18 23:40:23 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		return (1);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "|", 1) && ft_strncmp(str, "||", 2))
		return (1);
	return (0);
}

int	invalid_syntaxe(t_token_info *tokens, int i)
{
	if (!tokens[i + 1].content || is_redirect(tokens[i + 1].content)
		|| is_pipe(tokens[i + 1].content))
	{
		ft_putstr_fd("minishell: syntax error near `", 2);
		if (tokens[i + 1].content)
			ft_putstr_fd(tokens[i + 1].content, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

int	is_valid_syntax(t_token_info *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].content)
	{
		if (is_redirect(tokens[i].content))
			return (invalid_syntaxe(tokens, i));
		if (is_pipe(tokens[i].content))
		{
			if (i == 0 || !tokens[i + 1].content)
			{
				ft_putstr_fd("minishell: syntax error near `|'\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
