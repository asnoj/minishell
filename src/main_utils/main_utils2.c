/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:37:30 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 19:14:56 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (ft_strlen(s1) > n)
		return (1);
	if (n == 0)
		return (0);
	while (n - 1 > i && (str1[i] || str2[i]))
	{
		if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_tokens(t_token_info *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].content)
	{
		free(tokens[i].content);
		tokens[i].content = NULL;
		i++;
	}
	free(tokens);
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;
	t_list		*last;

	while (redir)
	{
		tmp = redir->next;
		while (redir->wild)
		{
			last = redir->wild->next;
			if (redir->wild->content)
				free(redir->wild->content);
			free(redir->wild);
			redir->wild = last;
		}
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}
