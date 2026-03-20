/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:34:56 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/20 21:50:24 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_heredoc(int pipefd[2], char **line)
{
	if (pipe(pipefd) < 0)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	setup_signals_heredoc();
	return (0);
}

static int	cleanup_heredoc(char *line, int pipefd[2])
{
	free(line);
	close(pipefd[0]);
	close(pipefd[1]);
	if (g_signal == SIGINT)
		g_signal = 0;
	return (-1);
}

static int	read_heredoc_lines(t_token *token, int pipefd[2], char **line)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("here_doc> ");
		if (buffer == NULL || g_signal == SIGINT)
			return (cleanup_heredoc(*line, pipefd));
		if (!ft_strncmp(token->redirects->file, buffer,
				ft_strlen(token->redirects->file) + 1))
		{
			free(buffer);
			break ;
		}
		buffer = add_new_line(buffer);
		*line = ft_strjoin(*line, buffer);
		free(buffer);
	}
	return (0);
}

int	collect_heredoc(t_token *token)
{
	char	*line;
	char	*expanded;
	int		pipefd[2];

	if (init_heredoc(pipefd, &line) < 0)
		return (-1);
	if (read_heredoc_lines(token, pipefd, &line) < 0)
		return (-1);
	expanded = expand_heredoc_line(line, token->env, 0);
	free(line);
	write(pipefd[1], expanded, ft_strlen(expanded));
	close(pipefd[1]);
	free(expanded);
	setup_signals_interactive();
	return (pipefd[0]);
}
