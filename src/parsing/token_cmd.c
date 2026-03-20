/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:38:08 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO more then one redirec out = just the last

#include "minishell.h"

static t_token	**refresh_head(t_token *current, t_token **head)
{
	t_token	**new_head;

	new_head = malloc(sizeof(t_token *));
	if (!new_head)
		return (NULL);
	*new_head = current;
	current->head = new_head;
	return (new_head);
}

static int	process_one_token(t_token_info *token_info,
		t_token *current, int i)
{
	i = fill_one_token(current, token_info, i);
	if (is_builtin_parent(current->command))
		current->skip = 1;
	return (i);
}

static t_token	**maybe_refresh(t_token *current, t_token **head,
		int need_refresh)
{
	if (!need_refresh)
		return (head);
	head = refresh_head(current, head);
	return (head);
}

static int	fsu_step(t_token_info *ti, t_token **cur,
		t_token ***head, t_token **cfst)
{
	int	cfst_refresh;

	cfst_refresh = (ti->content && or_and(ti, 0));
	if (cfst_refresh)
		(*cfst)->last_token = *cur;
	*cur = add_redirect_type(*cur, *ti, NULL);
	*head = maybe_refresh(*cur, *head, cfst_refresh);
	if (!*head)
		return (0);
	if (cfst_refresh)
		*cfst = *cur;
	(*cur)->head = *head;
	return (1);
}

void	fill_struct_utils(t_token_info *ti, t_token *cur,
		int i, t_token **head)
{
	t_token	*cfst_token;

	cfst_token = cur;
	while (ti[++i].content)
	{
		i = process_one_token(ti, cur, i);
		if (!fsu_step(&ti[i], &cur, &head, &cfst_token))
			return ;
		if (!ti[i].content)
			break ;
	}
	cfst_token->head = head;
	cfst_token->last_token = cur;
}
