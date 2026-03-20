/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 22:58:19 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_add_char(t_tokenizer *tok, char c)
{
	if (tok->state == STATE_NORMAL)
		return (!is_separator(c) && !is_quote(c));
	if (tok->state == STATE_IN_SINGLE_QUOTE)
		return (c != '\'');
	if (tok->state == STATE_IN_DOUBLE_QUOTE)
		return (c != '"');
	return (0);
}

void	skip_spaces(t_tokenizer *tok)
{
	while (tok->line[tok->i] && is_separator(tok->line[tok->i]))
		tok->i++;
}

int	is_separator(char c)
{
	if (c == ' ')
		return (TRUE);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
