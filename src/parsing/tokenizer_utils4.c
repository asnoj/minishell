/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:06:19 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 20:29:26 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_dollar_value(t_token_info *token_info, int i, int value, int start)
{
	token_info[i].dollar_start = value;
	token_info[i].dollar_end = value;
}

void	new_start(t_token_info *token_info, int i, char *start_ptr, int j)
{
	token_info[i].dollar_start = j;
	start_ptr = &token_info[i].content[j];
}

void	new_end(t_token_info *token_info, int i, char *end_ptr, int j)
{
	token_info[i].dollar_end = j;
	end_ptr = &token_info[i].content[j];
}

void	init_all_token_info(t_token_info *token_info)
{
	int		i;
	int		j;
	char	*start_ptr;
	char	*end_ptr;

	i = -1;
	while (token_info[++i].content)
	{
		j = -1;
		new_dollar_value(token_info, i, -1, 3);
		while (token_info[i].content[++j])
		{
			if ((token_info[i].content[j] == '$'
					&& token_info[i].dollar_start == -1))
				new_start(token_info, i, start_ptr, j);
			if (ft_isalpha(token_info[i].content[j])
				&& token_info[i].dollar_start != -1
				&& token_info[i].dollar_end == -1)
				new_end(token_info, i, end_ptr, j);
		}
		token_info[i].dollar_start_ptr = start_ptr;
		token_info[i].dollar_end_ptr = end_ptr;
	}
}
