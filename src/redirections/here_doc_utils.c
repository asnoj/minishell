/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:39:57 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:12:04 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_cancel(char *line, int *pipefd)
{
	free(line);
	close(pipefd[0]);
	close(pipefd[1]);
	if (g_signal == SIGINT)
		g_signal = 0;
	setup_signals_interactive();
	return (-1);
}

int	heredoc_finish(char *line, int *pipefd)
{
	write(pipefd[1], line, ft_strlen(line));
	close(pipefd[1]);
	free(line);
	setup_signals_interactive();
	return (pipefd[0]);
}

void	close_heredoc_fds(t_token *token)
{
	t_token		*tmp;
	t_redirect	*redir;

	tmp = token;
	while (tmp)
	{
		redir = tmp->redirects;
		while (redir)
		{
			if (redir->type == REDIRECT_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

void	prepare_all_heredocs(t_token *token)
{
	t_token		*temp;
	t_redirect	*redir;
	t_redirect	*saved;

	temp = token;
	while (temp)
	{
		redir = temp->redirects;
		while (redir)
		{
			if (redir->type == REDIRECT_HEREDOC)
			{
				saved = temp->redirects;
				temp->redirects = redir;
				redir->heredoc_fd = collect_heredoc(temp);
				temp->redirects = saved;
				if (redir->heredoc_fd == -1)
					return ;
			}
			else
				redir->heredoc_fd = -1;
			redir = redir->next;
		}
		temp = temp->next;
	}
}
