/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:55:12 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 18:55:42 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirect(t_redirect **redir, t_redirect *new)
{
	t_redirect	*current;

	if (*redir == NULL)
	{
		*redir = new;
		return ;
	}
	current = *redir;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

int	is_wild_card(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	verif_end_token(t_token_info *token_info, int i)
{
	if (token_info[i].content && 0 != ft_strncmpp("|", token_info[i].content, 1)
		&& token_info[i].content && 0 != ft_strncmpp("&&",
			token_info[i].content, 2) && token_info[i].content
		&& 0 != ft_strncmpp("||", token_info[i].content, 2))
		return (1);
	return (0);
}

int	skip_redir(t_token_info *token_info, int i, int redirect_type,
		t_token *token)
{
	if (token_info[i + 1].content)
	{
		if (FALSE == is_wild_card(token_info[i + 1].content))
		{
			add_redirect(&token->redirects, new_redirect(redirect_type,
					token_info[i + 1].content));
		}
		else
		{
			add_redirect(&token->redirects, new_redirect(redirect_type,
					token_info[i + 1].content));
			expand_wildcard(token_info[i + 1].content, token);
		}
		i += 2;
	}
	else
		i++;
	return (i);
}
