/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:51:23 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/18 20:32:05 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_operator(t_tokenizer *tok, char **current_token, int *rep)
{
	if (*rep != 0)
		return ;
	update_state(tok, tok->line[tok->i]);
	*current_token = add_char_to_str(*current_token, tok->line[tok->i++]);
	if (end_of_token(tok->line, tok->i) > 0)
	{
		update_state(tok, tok->line[tok->i]);
		*current_token = add_char_to_str(*current_token, tok->line[tok->i++]);
	}
}

static char	*fill_one_token_loop(t_tokenizer *tok, int *token_was_quoted)
{
	char	*current_token;
	int		rep;

	current_token = NULL;
	rep = 0;
	while (tok->line[tok->i] && !is_token_end(tok->line[tok->i], tok))
	{
		if (tok->state == STATE_IN_SINGLE_QUOTE
			|| tok->state == STATE_IN_DOUBLE_QUOTE)
			*token_was_quoted = 1;
		if (end_of_token(tok->line, tok->i) > 0)
		{
			handle_operator(tok, &current_token, &rep);
			break ;
		}
		update_state(tok, tok->line[tok->i]);
		current_token = add_char_to_str(current_token, tok->line[tok->i++]);
		rep = 1;
	}
	return (current_token);
}

void	fill_all_tokens(t_tokenizer *tok, t_token_info *str_tokens)
{
	int		token_was_quoted;

	while (tok->line[tok->i])
	{
		skip_spaces(tok);
		if (!tok->line[tok->i])
			break ;
		token_was_quoted = 0;
		tok->state = STATE_NORMAL;
		str_tokens[tok->tok_count].content = fill_one_token_loop(tok,
				&token_was_quoted);
		str_tokens[tok->tok_count].was_in_single_quote = token_was_quoted;
		tok->tok_count++;
	}
}
