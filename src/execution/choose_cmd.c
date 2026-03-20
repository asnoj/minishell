/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:00:59 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 20:20:51 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(int fd_in, int fd_out)
{
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
}

static int	cmd_not_found(t_token *token, int fd_in, int fd_out)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->command, 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds(fd_in, fd_out);
	return (127);
}

static void	child_exec(t_token *token, char *cmd_path, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	exec_cmd_with_path(token, cmd_path);
	exit(127);
}

int	exec_simple_cmd(t_token *token)
{
	int		fds[2];
	int		child;
	int		status;
	char	*path;

	fds[0] = return_fd(token, INPUT);
	fds[1] = return_fd(token->last_token, OUTPUT);
	if (fds[0] == -2 || fds[1] == -2)
		return (127);
	path = find_command(token);
	if (!path)
		return (cmd_not_found(token, fds[0], fds[1]));
	setup_signals_parent();
	child = fork();
	if (child == 0)
		child_exec(token, path, fds[0], fds[1]);
	free(path);
	close_fds(fds[0], fds[1]);
	if (child < 0)
		return (perror("fork"), setup_signals_interactive(), 1);
	waitpid(child, &status, 0);
	return (setup_signals_interactive(), WEXITSTATUS(status));
}

int	exec_simple_here_doc(t_token *token)
{
	int	child;
	int	status;

	setup_signals_parent();
	child = fork();
	if (child < 0)
		return (perror("fork"), 1);
	if (child == 0)
	{
		setup_signals_child();
		apply_heredoc_fd(token);
		exit(127);
	}
	close_heredoc_fds(token);
	waitpid(child, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	setup_signals_interactive();
	return (WEXITSTATUS(status));
}
