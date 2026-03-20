/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:05:12 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:15:46 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_path(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(char **s)
{
	int	n;

	if (!s)
		return ;
	n = 0;
	while (s[n])
	{
		free(s[n]);
		n++;
	}
	free(s);
}

void	free_transfo_err(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
}

char	**transfo(t_token *token)
{
	int		i;
	char	**envp;
	t_list	*envptr;

	envptr = token->env;
	i = 0;
	envp = malloc((ft_lstsize(token->env) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	while (envptr && envptr->content != NULL)
	{
		envp[i] = ft_strdup(envptr->content);
		if (!envp[i])
			return (free_transfo_err(envp, i), NULL);
		envptr = envptr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_cmd_not_found(char **av_cmd, char **envp, t_token *token)
{
	if (ft_strncmp("SPNjsO9y8A$3?RF5usaDGyYZd30WHLNIYjLp$$MI", token->command,
			41) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_during_pipe(token, envp, av_cmd);
	exit(127);
}
