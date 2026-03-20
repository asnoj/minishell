/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 22:58:25 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_end(char c, t_tokenizer *tok)
{
	if ('\0' == c)
		return (TRUE);
	else if (c == ' ' && STATE_NORMAL == tok->state)
		return (TRUE);
	return (FALSE);
}

void	update_state(t_tokenizer *tok, char c)
{
	if (tok->state == STATE_NORMAL)
	{
		if (c == '\'')
			tok->state = STATE_IN_SINGLE_QUOTE;
		else if (c == '"')
			tok->state = STATE_IN_DOUBLE_QUOTE;
	}
	else if (tok->state == STATE_IN_SINGLE_QUOTE && c == '\'')
		tok->state = STATE_NORMAL;
	else if (tok->state == STATE_IN_DOUBLE_QUOTE && c == '"')
		tok->state = STATE_NORMAL;
}

char	*add_char_to_str(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}
