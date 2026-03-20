/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 16:57:39 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	skip_command_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	skip_n_flags(char *str, int i, int *newline)
{
	int	start;

	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != ' ')
			i++;
		if (!is_n_flag_range(str, start, i))
		{
			return (start);
		}
		*newline = 0;
		while (str[i] == ' ')
			i++;
	}
	return (i);
}

int	is_n_flag_range(char *str, int start, int end)
{
	int	i;

	if (str[start] != '-' || start + 1 >= end)
		return (0);
	i = start + 1;
	while (i < end)
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_token *token)
{
	char	*cmd;
	int		i;
	int		fd;
	int		newline;

	if (!token->command)
		return (1);
	cmd = token->command;
	newline = 1;
	i = skip_command_name(cmd);
	i = skip_n_flags(cmd, i, &newline);
	fd = return_fd(token, OUTPUT);
	if (fd == -1)
		fd = 0;
	write(fd, &cmd[i], ft_strlen(&cmd[i]));
	if (newline)
		write(fd, "\n", 1);
	return (0);
}
