/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:44:03 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 22:14:43 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipeline_wait(int child)
{
	int	status;
	int	res;

	res = 0;
	if (child > 0)
	{
		waitpid(child, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		res = WEXITSTATUS(status);
	}
	else
		perror("fork");
	setup_signals_interactive();
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		write(1, "\n", 1);
	}
	return (res);
}

int	exec_pipeline(t_token *token)
{
	int	child;
	int	res;

	setup_signals_parent();
	child = fork();
	if (child == 0)
	{
		setup_signals_child();
		if (token->redirects->type == REDIRECT_HEREDOC)
			res = child_set_doc(token);
		else
			res = child_set(token);
		exit(EXIT_FAILURE);
	}
	close_heredoc_fds(token);
	return (pipeline_wait(child));
}
