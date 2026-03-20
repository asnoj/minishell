/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:15:16 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 16:57:34 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_backk(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next->next != NULL)
		current = current->next;
	temp = current->next;
	current->next = new;
	current->next->next = temp;
}

void	fill_env(t_token *token, char **envp)
{
	int		i;
	t_list	*new_node;
	char	*old_path;
	char	*spawn;

	if (!envp || !envp[0])
	{
		token->env = NULL;
		return ;
	}
	i = 0;
	token->env = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		if (!new_node)
			return ;
		ft_lstadd_backk(&token->env, new_node);
		i++;
	}
}

char	*expend_valid(t_token *token, t_token_info *token_info)
{
	t_list	*current;
	int		expend_len;

	expend_len = token_info->dollar_end - token_info->dollar_start;
	current = token->env;
	while (current != NULL)
	{
		if (ft_strncmpp(token_info->dollar_start_ptr, (char *)current->content,
				expend_len))
			return ((char *)current->content);
		current = current->next;
	}
	return (NULL);
}

char	*expand(t_token *token, t_token_info *token_info)
{
	char	*line;
	int		i;

	i = 0;
	line = expend_valid(token, token_info);
	if (line != NULL)
	{
		while (line[i] && line[i] != '=')
			i++;
		if (line[i] == '=')
		{
			free(token_info->content);
			token_info->content = ft_strdup(&line[i + 1]);
		}
	}
	return (token_info->content);
}
