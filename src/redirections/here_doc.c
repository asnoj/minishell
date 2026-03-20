/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 03:29:16 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:33:47 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_linee(ssize_t bytes_read, char *buffer, char *LIMITEUR)
{
	char	op[20];
	int		j;
	int		i;

	i = 0;
	while (i < bytes_read)
	{
		while (i < bytes_read && (buffer[i] == '\n' || buffer[i] == ' '))
			i++;
		if (i >= bytes_read)
			break ;
		j = 0;
		while (i < bytes_read && buffer[i] != '\n' && buffer[i] != ' '
			&& j < 19)
			op[j++] = buffer[i++];
		op[j] = 0;
		if (j > 0)
			return (ft_strncmp(LIMITEUR, op, ft_strlen(op) + 1));
	}
	return (1);
}

void	doc_process_pipe(t_token *token, char *line)
{
	int	fd;

	fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(token->pipe_fd[0]);
		close(token->pipe_fd[1]);
		perror(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	write(fd, line, ft_strlen(line));
	close(fd);
	fd = open("temp", O_RDONLY);
	if (fd < 0)
	{
		close(token->pipe_fd[0]);
		close(token->pipe_fd[1]);
		perror(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	dup2(token->pipe_fd[1], STDOUT_FILENO);
	(close(fd), close(token->pipe_fd[0]));
	close(token->pipe_fd[1]);
	exec_cmd(token);
}

void	here_doc_pipe(char *LIMITEUR, char *cmd, t_token *token)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*line;
	int		fd;

	(void)cmd;
	fd = 0;
	line = malloc(1024);
	line[0] = '\0';
	bytes_read = read(fd, buffer, 1024 - 1);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		if (!end_linee(bytes_read, buffer, LIMITEUR))
		{
			doc_process_pipe(token, line);
			free(line);
			return ;
		}
		line = ft_strjoin(line, buffer);
		bytes_read = read(fd, buffer, 1024 - 1);
		buffer[bytes_read] = '\0';
	}
}

void	fill(t_token *token)
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

int	child_set_doc(t_token *token)
{
	int	nb_fork1;
	int	status;

	if (pipe(token->pipe_fd) < 0)
		error_fuction(token->pipe_fd);
	nb_fork1 = fork();
	if (nb_fork1 < 0)
		error_fuction(token->pipe_fd);
	if (nb_fork1 == 0)
		apply_heredoc_pipe(token);
	dup2(token->pipe_fd[0], STDIN_FILENO);
	fill(token);
	close(token->pipe_fd[0]);
	close(token->pipe_fd[1]);
	waitpid(nb_fork1, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}
