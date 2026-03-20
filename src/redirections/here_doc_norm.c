/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:25:17 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:17:07 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_heredoc_fd(t_token *token)
{
	t_redirect	*redir;
	int			fd;

	redir = token->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_HEREDOC && redir->heredoc_fd >= 0)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
	fd = return_fd(token, OUTPUT);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	exec_cmd(token);
}

void	apply_heredoc_pipe(t_token *token)
{
	t_redirect	*redir;
	int			fd;

	redir = token->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_HEREDOC && redir->heredoc_fd >= 0)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
	dup2(token->pipe_fd[1], STDOUT_FILENO);
	close(token->pipe_fd[0]);
	close(token->pipe_fd[1]);
	exec_cmd(token);
}

char	*add_new_line(char *line)
{
	int		len;
	char	*str;
	int		i;

	len = ft_strlen(line);
	str = malloc(len + 2);
	if (!str)
		return (line);
	i = -1;
	while (line[++i])
		str[i] = line[i];
	str[i] = '\n';
	str[i + 1] = '\0';
	free(line);
	return (str);
}

static char	*heredoc_read_loop(t_token *token, char *line)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("here_doc> ");
		if (buffer == NULL || g_signal == SIGINT)
			return (NULL);
		if (!ft_strncmp(token->redirects->file, buffer,
				ft_strlen(token->redirects->file) + 1))
		{
			free(buffer);
			return (line);
		}
		buffer = add_new_line(buffer);
		line = ft_strjoin(line, buffer);
		free(buffer);
	}
}

void	here_doc(t_token *token)
{
	token->redirects->heredoc_fd = collect_heredoc(token);
}
