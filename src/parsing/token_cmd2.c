/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 00:08:12 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_redirect_list(t_token *token, t_redirect *last_in,
		t_redirect *last_out)
{
	if (last_in)
		last_in->next = last_out;
	if (last_out)
		last_out->next = NULL;
	if (last_in)
		token->redirects = last_in;
	else
		token->redirects = last_out;
}

static char	**alloc_tokens(int count)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	tokens[count] = NULL;
	return (tokens);
}

static int	should_keep(t_redirect *cur, t_redirect *last_in,
		t_redirect *last_out)
{
	if (cur == last_in || cur == last_out)
		return (1);
	if (cur->type == REDIRECT_HEREDOC)
		return (1);
	if (cur->type == REDIRECT_PIPE_IN || cur->type == REDIRECT_PIPE_OUT)
		return (1);
	if (cur->type == REDIRECT_AND || cur->type == REDIRECT_OR)
		return (1);
	return (0);
}

static void	append_or_free(t_redirect *current, t_redirect *last_in,
		t_redirect *last_out, t_redirect **list)
{
	if (should_keep(current, last_in, last_out))
	{
		current->next = NULL;
		if (!list[0])
			list[0] = current;
		else
			list[1]->next = current;
		list[1] = current;
	}
	else
		free_one_redirect(current);
}

void	remove_duplicate_redirects(t_token *token)
{
	t_redirect	*last_in;
	t_redirect	*last_out;
	t_redirect	*current;
	t_redirect	*tmp;
	t_redirect	*list[2];

	if (!token || !token->redirects)
		return ;
	last_in = find_last_redirect(token->redirects, REDIRECT_IN,
			REDIRECT_HEREDOC);
	last_out = find_last_redirect(token->redirects, REDIRECT_OUT,
			REDIRECT_APPEND);
	list[0] = NULL;
	list[1] = NULL;
	current = token->redirects;
	while (current)
	{
		tmp = current->next;
		append_or_free(current, last_in, last_out, list);
		current = tmp;
	}
	token->redirects = list[0];
}
