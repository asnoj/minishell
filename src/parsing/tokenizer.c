/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:56:49 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_info	*strs_tokenizer(char *line, t_token *token)
{
	t_token_info	*token_info;
	t_tokenizer		*tok;

	tok = init_tok(line);
	token_info = malloc(sizeof(t_token_info) * 1024);
	fill_all_tokens(tok, token_info);
	token_info[tok->tok_count].content = NULL;
	token_info[tok->tok_count].was_in_single_quote = 0;
	free(tok);
	init_all_token_info(token_info);
	expand_all_tokens(token_info, token);
	return (token_info);
}

int	end_of_token(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	if (str[i] && str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			return (2);
		return (1);
	}
	if (str[i] && str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}
