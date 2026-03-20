/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd2_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 20:34:31 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_w_all(t_token *token, t_redirect *last_in,
		t_redirect *last_out)
{
	(void)token;
	(void)last_in;
	(void)last_out;
}

void	clean_all_redirects(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		remove_duplicate_redirects(current);
		current = current->next;
	}
}

t_redirect	*find_last_redirect(t_redirect *redir, int type1, int type2)
{
	t_redirect	*last;

	last = NULL;
	while (redir)
	{
		if (redir->type == type1 || redir->type == type2)
			last = redir;
		redir = redir->next;
	}
	return (last);
}
