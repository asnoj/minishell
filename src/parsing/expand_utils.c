/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:45:23 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/17 18:11:39 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

void	update_state_extand(int *state, char c)
{
	if (*state == STATE_NORMAL && c == '\'')
		*state = STATE_IN_SINGLE_QUOTE;
	else if (*state == STATE_NORMAL && c == '"')
		*state = STATE_IN_DOUBLE_QUOTE;
	else if (*state == STATE_IN_SINGLE_QUOTE && c == '\'')
		*state = STATE_NORMAL;
	else if (*state == STATE_IN_DOUBLE_QUOTE && c == '"')
		*state = STATE_NORMAL;
}

t_token_info	*expand_all_tokens(t_token_info *token_info, t_token *token)
{
	int		i;
	char	*expanded;

	i = -1;
	while (token_info[++i].content)
	{
		if (i > 0 && ft_strncmpp(token_info[i - 1].content, "<<", 2) == 0)
			continue ;
		expanded = expand_token_content(token_info[i].content,
				token->env, *token->exit_signal);
		free(token_info[i].content);
		token_info[i].content = expanded;
	}
	return (token_info);
}
