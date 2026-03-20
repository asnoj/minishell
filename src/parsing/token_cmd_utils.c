/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:37:11 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:56:56 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_one_token(t_token *token, t_token_info *token_info, int i)
{
	int	redirect_type;

	while (verif_end_token(token_info, i))
	{
		redirect_type = get_redirect_type(token_info[i].content);
		if (redirect_type && token_info[i].was_in_single_quote == FALSE)
			i = skip_redir(token_info, i, redirect_type, token);
		else if (ft_strncmp(token->command,
				"SPNjsO9y8A$3?RF5usaDGyYZd30WHLNIYjLp$$MI", 41) == 0)
		{
			free(token->command);
			token->command = ft_strdup(token_info[i].content);
			i++;
		}
		else
		{
			token->command = add_char_to_str(token->command, ' ');
			token->command = ft_strjoin(token->command, token_info[i].content);
			i++;
		}
	}
	return (i);
}

t_token	*add_redirect_type(t_token *current, t_token_info token_info, int *i)
{
	if (token_info.content && 0 == ft_strncmp(token_info.content, "|", 1))
	{
		add_redirect(&current->redirects, new_redirect(REDIRECT_PIPE_OUT,
				NULL));
		current->next = new_token();
		current = current->next;
		add_redirect(&current->redirects, new_redirect(REDIRECT_PIPE_IN, NULL));
	}
	if (token_info.content && 0 == ft_strncmpp(token_info.content, "||", 2))
	{
		add_redirect(&current->redirects, new_redirect(REDIRECT_OR, "NONE"));
		current->next = new_token();
		current = current->next;
		add_redirect(&current->redirects, new_redirect(REDIRECT_OR, "NONE"));
	}
	if (token_info.content && 0 == ft_strncmpp(token_info.content, "&&", 2))
	{
		add_redirect(&current->redirects, new_redirect(REDIRECT_AND, "NONE"));
		current->next = new_token();
		current = current->next;
		add_redirect(&current->redirects, new_redirect(REDIRECT_AND, "NONE"));
	}
	return (current);
}

int	or_and(t_token_info *token_info, int i)
{
	if ((0 == ft_strncmpp(token_info[i].content, "&&", 2)
			|| 0 == ft_strncmpp(token_info[i].content, "||", 2)))
		return (1);
	return (0);
}

t_token	*fill_struct(t_token_info *token_info, char **env)
{
	t_token	*token;
	t_token	**head;

	(void)env;
	token = new_token();
	if (!token)
		return (NULL);
	head = malloc(sizeof(t_token *));
	if (!head)
		return (NULL);
	*head = token;
	token->head = head;
	fill_struct_utils(token_info, token, -1, head);
	return (token);
}
