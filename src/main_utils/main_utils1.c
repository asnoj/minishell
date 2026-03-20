/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:46:48 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:52:11 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token		*tmp;
	t_token		**last_head;
	t_token		**current_head;

	last_head = NULL;
	while (token)
	{
		tmp = token->next;
		current_head = token->head;
		if (current_head && current_head != last_head)
		{
			if (last_head)
				free(last_head);
			last_head = current_head;
		}
		if (token->command)
			free(token->command);
		if (token->args)
			free(token->args);
		free_redirects(token->redirects);
		free(token);
		token = tmp;
	}
	if (last_head)
		free(last_head);
}

void	free_env_list(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->content);
		free(env);
		env = tmp;
	}
}

int	is_builtin_parent(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmpp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmpp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmpp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmpp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_token *token)
{
	if (!token->command)
		return ;
	if (ft_strncmp(token->command, "pwd", 3) == 0)
		ft_pwd(token);
	else if (ft_strncmpp(token->command, "cd", 2) == 0)
		builtin_cd(token);
	else if (ft_strncmp(token->command, "env", 3) == 0)
		cmd_env(token);
	else if (ft_strncmpp(token->command, "export", 6) == 0)
		ft_export(token);
	if (ft_strncmpp(token->command, "unset", 5) == 0)
		token->env = ft_unset(token);
}

void	update_all_tokens_env(t_token *commands, t_list *env)
{
	t_token	*current;

	current = commands;
	while (current)
	{
		current->env = env;
		current = current->next;
	}
}
