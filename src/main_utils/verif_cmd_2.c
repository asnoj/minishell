/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:31:34 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 22:23:24 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token_output(t_token *token)
{
	t_redirect	*current;
	t_list		*w;

	current = new_redirect(token->redirects->type, token->redirects->file);
	w = token->redirects->wild;
	while (w)
	{
		ft_lstadd_backk(&current->wild, ft_lstnew(w->content));
		w = w->next;
	}
	free_redirects(token->redirects);
	token->redirects = new_redirect(REDIRECT_IN, "NONE");
	add_redirect(&token->redirects, new_redirect(current->type, current->file));
	w = current->wild;
	while (w)
	{
		ft_lstadd_backk(&token->redirects->next->wild, ft_lstnew(w->content));
		w = w->next;
	}
	free_redirects(current);
}

void	advance_past_pipes(t_token **temp)
{
	while ((*temp)->next != NULL && is_output_input_pipe(OUTPUT,
			*temp) == REDIRECT_PIPE_OUT)
		*temp = (*temp)->next;
	*temp = (*temp)->next;
}

int	get_operator_type(t_token *token)
{
	t_redirect	*redir;
	int			last;

	if (!token || !token->redirects)
		return (0);
	last = 0;
	redir = token->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_AND || redir->type == REDIRECT_OR
			|| redir->type == REDIRECT_PIPE_OUT)
			last = redir->type;
		redir = redir->next;
	}
	return (last);
}

t_token	*init_token(t_token *token)
{
	if (!token->redirects)
		token->redirects = new_redirect(0, "NONE");
	else if (is_output_type(token->redirects->type))
		init_token_output(token);
	if (!token->last_token)
		token->last_token = token;
	if (!token->last_token->redirects->next)
		token->last_token->redirects->next = new_redirect(0, "NONE");
	return (token);
}

int	ft_exec_output(t_token *temp, t_list *str)
{
	int	res;

	res = 0;
	temp->last_token->redirects->next->file = ft_strdup((char *)str->content);
	if (is_output_input_pipe(OUTPUT, temp) == REDIRECT_PIPE_OUT)
		res = exec_pipeline(temp);
	else if (temp->redirects != NULL
		&& temp->redirects->type == REDIRECT_HEREDOC)
		res = exec_simple_here_doc(temp);
	else if (ft_strncmpp(temp->command, "echo", 4) == 0
		&& (temp->command[4] == ' ' || temp->command[4] == '\0'))
		builtin_echo(temp);
	else
		res = exec_simple_cmd(temp);
	return (res);
}
