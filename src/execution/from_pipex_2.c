/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipex_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:27:25 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 17:11:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(t_token *token)
{
	char	**path_dirs;
	char	*cmd_name;

	cmd_name = get_cmd_name(token->command);
	if (!cmd_name)
		return (NULL);
	if (cmd_name[0] == '/' || (cmd_name[0] == '.' && cmd_name[1] == '/'))
		return (check_direct_path(cmd_name));
	path_dirs = find_path(token);
	if (!path_dirs)
		return (free(cmd_name), NULL);
	return (search_in_path(path_dirs, cmd_name));
}

char	*get_cmd_name(char *cmd)
{
	int		i;
	char	*name;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (perror("minishell: malloc"), NULL);
	ft_strlcpy(name, cmd, i + 1);
	return (name);
}

char	**find_path(t_token *token)
{
	char	**path;
	t_list	*envp;

	envp = token->env;
	while (envp != NULL && envp->content != NULL)
	{
		if (ft_strncmpp(envp->content, "PATH=", 5) == 0)
		{
			path = ft_split(&((char *)envp->content)[5], ':');
			if (!path)
				return (NULL);
			return (path);
		}
		envp = envp->next;
	}
	ft_putstr_fd("minishell: PATH not found in environment\n", 2);
	return (NULL);
}

void	exec_cmd_with_path(t_token *token, char *cmd_path)
{
	char	**av_cmd;
	char	**envp;

	if (!token->command || !cmd_path)
		exit(EXIT_FAILURE);
	av_cmd = ft_split(token->command, ' ');
	if (!av_cmd)
		return (free(cmd_path), exit(EXIT_FAILURE));
	envp = transfo(token);
	if (!envp)
		return (free_all(av_cmd), free(cmd_path), exit(EXIT_FAILURE));
	execve(cmd_path, av_cmd, envp);
	perror("minishell");
	free_all(envp);
	free_all(av_cmd);
	free(cmd_path);
	exit(127);
}

int	exec_cmd(t_token *token)
{
	char	*cmd_path;
	char	**av_cmd;
	char	**envp;

	if (!token->command)
		return (1);
	if (ft_strncmpp(token->command, "exit", 4) == 0)
		builtin_exit(token);
	av_cmd = ft_split(token->command, ' ');
	if (!av_cmd)
		return (perror("minishell: ft_split"), exit(EXIT_FAILURE), 1);
	envp = transfo(token);
	if (!envp)
		return (free_all(av_cmd), perror("minishell: transfo"),
			exit(EXIT_FAILURE), 1);
	cmd_path = find_command(token);
	if (!cmd_path)
		exec_cmd_not_found(av_cmd, envp, token);
	execve(cmd_path, av_cmd, envp);
	perror("minishell: execve");
	free_all(envp);
	free_all(av_cmd);
	free(cmd_path);
	exit(127);
}
