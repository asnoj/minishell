/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sturct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:59:29 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/20 21:05:10 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirect_type(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmpp(str, ">>", 2))
		return (REDIRECT_APPEND);
	if (!ft_strncmpp(str, "<<", 2))
		return (REDIRECT_HEREDOC);
	if (!ft_strncmpp(str, ">", 1))
		return (REDIRECT_OUT);
	if (!ft_strncmpp(str, "<", 1))
		return (REDIRECT_IN);
	return (0);
}

int	is_operator(char *str)
{
	if (!str)
		return (0);
	if (get_redirect_type(str))
		return (1);
	if (!ft_strncmpp(str, "|", 1))
		return (1);
	return (0);
}

char	*pars_here_doc(char *file)
{
	int		i;
	char	**strs;
	char	*result;

	strs = ft_split(file, '"');
	if (!strs || strs[0] == NULL)
	{
		free_all_split(strs, 0);
		return (ft_strdup(""));
	}
	i = 0;
	result = NULL;
	while (strs[i])
	{
		if (!result)
			result = ft_strdup(strs[i]);
		else
			result = ft_strjoin(result, strs[i]);
		i++;
	}
	free_all_split(strs, i);
	if (!result)
		return (ft_strdup(""));
	return (result);
}

t_redirect	*new_redirect(int type, char *file)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (file != NULL)
	{
		if (type == REDIRECT_HEREDOC)
			redir->file = pars_here_doc(file);
		else
			redir->file = ft_strdup(file);
	}
	else
		redir->file = NULL;
	redir->wild = ft_lstnew(redir->file);
	redir->next = NULL;
	return (redir);
}

t_token	*new_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = ft_strdup("SPNjsO9y8A$3?RF5usaDGyYZd30WHLNIYjLp$$MI");
	token->head = NULL;
	token->args = NULL;
	token->args_i = 0;
	token->skip = 0;
	token->pipe_fd[0] = -1;
	token->pipe_fd[1] = -1;
	token->env = NULL;
	token->redirects = NULL;
	token->next = NULL;
	token->last_token = NULL;
	return (token);
}
