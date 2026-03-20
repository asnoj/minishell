/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:36:32 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 20:43:25 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_exist(t_token *token, char *str, int i)
{
	t_list	*lst;
	t_list	*prev;

	lst = token->env;
	prev = NULL;
	while (lst != NULL)
	{
		if (ft_strncmpp((char *)lst->content, str, i) == 0)
		{
			if (prev == NULL)
				token->env = lst->next;
			else
				prev->next = lst->next;
			free(lst->content);
			free(lst);
			return (token->env);
		}
		prev = lst;
		lst = lst->next;
	}
	return (token->env);
}

char	*ft_export_exp(char *str, int i, t_token *token, t_list *lst)
{
	token->env = env_exist(token, str, i);
	lst = ft_lstnew(str);
	if (!lst)
	{
		free(str);
		return (NULL);
	}
	ft_lstadd_back(&token->env, lst);
	free(str);
	return (NULL);
	i++;
}

char	*ft_export_null(char *str, int i, t_token *token, t_list *lst)
{
	token->env = env_exist(token, str, i);
	lst = ft_lstnew(str);
	if (!lst)
	{
		free(str);
		return (NULL);
	}
	ft_lstadd_back(&token->env, lst);
	free(str);
	return (NULL);
	i++;
}

char	*ft_export(t_token *token)
{
	int		i;
	char	*str;
	t_list	*lst;

	i = 0;
	i = export_skip_to_space(i, token);
	if (!token->command[i])
		return (print_for_export(token), NULL);
	str = ft_strdup(&token->command[i + 1]);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_export_exp(str, i, token, lst));
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	if (str[i] && !ft_isalnum(str[i]))
		return (ft_export_utils(str));
	return (ft_export_null(str, i, token, lst));
}

char	*ft_pwd(t_token *token)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("error during execution");
		return (0);
	}
	if (ft_strncmpp(token->command, "pwd", 3) == 0)
		printf("you are :%s\n", buffer);
	if (ft_strncmpp(token->command, "pwd", 3) == 0)
		return (free(buffer), NULL);
	else
		return (buffer);
}
