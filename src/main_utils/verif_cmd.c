/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:47:09 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:05:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	other_cmd(t_token *token)
{
	t_token	*temp;
	t_list	*current_input;
	t_list	*current_output;
	int		res;

	token = init_token(token);
	temp = token;
	current_input = temp->redirects->wild;
	current_output = temp->last_token->redirects->next->wild;
	while (current_input != NULL)
	{
		if (temp->redirects->file != NULL)
			free(token->redirects->file);
		temp->redirects->file = ft_strdup((char *)current_input->content);
		while (current_output != NULL)
		{
			if (temp->last_token->redirects->next->file != NULL)
				free(temp->last_token->redirects->next->file);
			res = ft_exec_output(temp, current_output);
			current_output = current_output->next;
		}
		current_input = current_input->next;
		current_output = temp->last_token->redirects->next->wild;
	}
	return (res);
}

int	handle_empty_cmd(t_token **temp, int *prev_type)
{
	ft_putstr_fd("minishell: : command not found\n", 2);
	*prev_type = get_operator_type(*temp);
	*temp = (*temp)->next;
	return (127);
}

void	skip_token(int *prev_type, t_token **temp, int *status)
{
	*prev_type = get_operator_type(*temp);
	if (*prev_type == REDIRECT_OR && (*temp)->redirects->next
		&& (*temp)->redirects->next->type == REDIRECT_AND)
	{
		*prev_type = REDIRECT_AND;
		*status = 0;
	}
	advance_past_pipes(temp);
}

int	process_token(t_token **temp, int *status, int *prev_type)
{
	if (!(*temp)->command || (*temp)->command[0] == '\0')
	{
		*status = handle_empty_cmd(temp, prev_type);
		return (1);
	}
	if (should_skip_token(*prev_type, *status))
	{
		skip_token(prev_type, temp, status);
		return (1);
	}
	if (ft_strncmpp((*temp)->command, "exit", 4) == 0)
	{
		*status = fast_builtin_exit((*temp)->command);
		return (-1);
	}
	else if (is_builtin_parent((*temp)->command) && is_output_input_pipe(OUTPUT,
			*temp) != REDIRECT_PIPE_OUT)
		exec_builtin(*temp);
	else
		*status = other_cmd(*temp);
	*prev_type = get_operator_type(*temp);
	advance_past_pipes(temp);
	return (0);
}

int	verif_command(t_token *token)
{
	int		status;
	int		child;
	int		prev_type;
	t_token	*temp;

	prepare_all_heredocs(token);
	if (g_signal == SIGINT)
		return (130);
	temp = token;
	status = 0;
	prev_type = 0;
	while (temp != NULL)
	{
		if (process_token(&temp, &status, &prev_type) == -1)
		{
			token = temp;
			break ;
		}
	}
	close_heredoc_fds(token);
	return (status);
}
