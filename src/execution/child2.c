/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:01:57 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 22:14:59 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_dup_pipe(int *pipe_fd, char *cmd, t_token *token)
{
	int	fd_in;
	int	fd_out;

	fd_in = find_input_fd(token);
	fd_out = find_output_fd(token);
	if (fd_in >= 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(token);
}

void	child2_process(int *pipe_fd, char *cmd, t_token *token, char *nametxt)
{
	int	fd;

	fd = return_fd(token, OUTPUT);
	if (fd < -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	close(pipe_fd[1]);
	exec_cmd(token);
}

void	fill_child(t_token *token)
{
	int		nb_fork2;
	int		status;
	t_token	*index;

	index = token->next;
	while (index->next != NULL)
	{
		close(token->pipe_fd[0]);
		close(token->pipe_fd[1]);
		if (pipe(token->pipe_fd) < 0)
			error_fuction(token->pipe_fd);
		nb_fork2 = fork();
		if (nb_fork2 < 0)
			error_fuction(token->pipe_fd);
		if (nb_fork2 == 0)
			child_dup_pipe(token->pipe_fd, index->command, index);
		dup2(token->pipe_fd[0], STDIN_FILENO);
		index = index->next;
	}
	child2_process(token->pipe_fd, index->command, token->last_token,
		is_output_input(OUTPUT, index));
	close(token->pipe_fd[0]);
	close(token->pipe_fd[1]);
	waitpid(nb_fork2, &status, 0);
}

int	child_set(t_token *token)
{
	int	nb_fork1;
	int	status;
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (pipe(token->pipe_fd) < 0)
		error_fuction(token->pipe_fd);
	nb_fork1 = fork();
	if (nb_fork1 < 0)
		error_fuction(token->pipe_fd);
	if (nb_fork1 == 0)
	{
		close(saved_stdin);
		child1_process(token->pipe_fd, token->command, token,
			is_output_input(INPUT, token));
	}
	dup2(token->pipe_fd[0], STDIN_FILENO);
	close(saved_stdin);
	fill_child(token);
	close(token->pipe_fd[0]);
	close(token->pipe_fd[1]);
	waitpid(nb_fork1, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}
