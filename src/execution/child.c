/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:02:58 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 22:14:56 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_input_fd(t_token *token)
{
	t_redirect	*redir;

	if (!token || !token->redirects)
		return (-1);
	redir = token->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_HEREDOC && redir->heredoc_fd >= 0)
			return (redir->heredoc_fd);
		if (redir->type == REDIRECT_IN && redir->file
			&& ft_strncmpp(redir->file, "NONE", 4) != 0)
			return (open(redir->file, O_RDONLY));
		redir = redir->next;
	}
	return (-1);
}

int	find_output_fd(t_token *token)
{
	t_redirect	*redir;

	if (!token || !token->redirects)
		return (-1);
	redir = token->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_OUT && redir->file
			&& ft_strncmpp(redir->file, "NONE", 4) != 0)
			return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
		if (redir->type == REDIRECT_APPEND && redir->file
			&& ft_strncmpp(redir->file, "NONE", 4) != 0)
			return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
		redir = redir->next;
	}
	return (-1);
}

int	return_fd(t_token *token, t_inout inout)
{
	int			fd;
	t_redirect	*temp;

	temp = token->redirects;
	fd = -1;
	if (inout == OUTPUT)
	{
		if (temp->next == NULL || temp->next->file == NULL
			|| ft_strncmpp(temp->next->file, "NONE", 4) == 0)
			return (fd);
		if (temp->next->type == REDIRECT_APPEND)
			fd = open(temp->next->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (temp->next->type == REDIRECT_OUT)
			fd = open(temp->next->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (inout == INPUT)
	{
		if (temp->file == NULL || ft_strncmpp(temp->file, "NONE", 4) == 0
			|| temp->type == REDIRECT_HEREDOC)
			return (fd);
		fd = open(temp->file, O_RDONLY);
	}
	if (fd <= -1)
		return (-2);
	return (fd);
}

void	child1_process(int *pipe_fd, char *cmd, t_token *token, char *nametxt)
{
	int	fd;

	fd = find_input_fd(token);
	if (fd == -1)
		fd = return_fd(token, INPUT);
	if (fd < -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(token);
}
