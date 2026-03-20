/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:59:00 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 17:00:37 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_to_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

static t_list	*unset_find_and_remove(t_token *token, char *str)
{
	t_list	*lst;
	t_list	*prev;

	lst = token->env;
	prev = NULL;
	while (lst != NULL)
	{
		if (ft_strncmpp((char *)lst->content, str, ft_strlen(str)) == 0)
		{
			if (prev == NULL)
				token->env = lst->next;
			else
				prev->next = lst->next;
			free(lst->content);
			free(lst);
			return (free(str), token->env);
		}
		prev = lst;
		lst = lst->next;
	}
	printf("the var doesn't exist\n");
	return (free(str), token->env);
}

t_list	*ft_unset(t_token *token)
{
	int		i;
	char	*str;

	i = skip_to_space(token->command);
	if (i == -1)
	{
		cmd_env(token);
		return (token->env);
	}
	str = ft_strdup(&token->command[i + 1]);
	return (unset_find_and_remove(token, str));
}
