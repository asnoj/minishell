/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipex_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:28:36 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:21:48 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_direct_path(char *cmd_name)
{
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	free(cmd_name);
	return (NULL);
}

char	*search_in_path(char **path_dirs, char *cmd_name)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = malloc(ft_strlen(path_dirs[i]) + ft_strlen(cmd_name) + 2);
		if (!full_path)
			return (free_all(path_dirs), free(cmd_name), NULL);
		full_path = ft_join_all(full_path, path_dirs, cmd_name, i);
		if (access(full_path, X_OK) == 0)
			return (free(cmd_name), free_all(path_dirs), full_path);
		free(full_path);
		i++;
	}
	free_all(path_dirs);
	free(cmd_name);
	return (NULL);
}

void	free_during_pipe(t_token *token, char **envp, char **av_cmd)
{
	close_heredoc_fds(*token->head);
	free_env_list((*token->head)->env);
	free_token_list(*token->head);
	if (envp != NULL)
		free_all(envp);
	if (av_cmd != NULL)
		free_all(av_cmd);
}
