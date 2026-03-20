/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:37:50 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 00:10:02 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fnmatch_quote(char *pattern, char *str, int i, int j)
{
	if (ft_fnmatch(pattern, str, i + 1, j + 1) == 0)
		return (0);
	return (1);
}

int	ft_fnmatch(char *pattern, char *str, int i, int j)
{
	if (pattern[i] == '\0' && str[j] == '\0')
		return (0);
	if (pattern[i] == '\0')
		return (1);
	if (str[j] == '\0')
	{
		if (pattern[i] == '*')
			return (ft_fnmatch(pattern, str, i + 1, j));
		return (1);
	}
	if (pattern[i] == '*')
	{
		if (ft_fnmatch(pattern, str, i + 1, j) == 0)
			return (0);
		if (ft_fnmatch(pattern, str, i, j + 1) == 0)
			return (0);
		return (1);
	}
	if (pattern[i] == '?')
		return (fnmatch_quote(pattern, str, i, j));
	if (pattern[i] == '[')
		return (fnmatch_crochet(pattern, str, i, j));
	if (pattern[i] == str[j])
		return (ft_fnmatch(pattern, str, i + 1, j + 1));
	return (1);
}

void	utils_for_wildcard(char *filename, DIR *dir, t_token *token,
		t_list *new)
{
	if (!filename)
	{
		closedir(dir);
		return ;
	}
	new = ft_lstnew(filename);
	if (!new)
	{
		free(filename);
		closedir(dir);
		return ;
	}
	if (token->redirects->next)
		ft_lstadd_backk(&token->redirects->next->wild, new);
	else
		ft_lstadd_backk(&token->redirects->wild, new);
}

void	expand_wildcard(char *pattern, t_token *token)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new;
	char			*filename;

	dir = opendir(".");
	if (!dir)
		return (perror("opendir"));
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			if (ft_fnmatch(pattern, entry->d_name, 0, 0) == 0)
			{
				filename = ft_strdup(entry->d_name);
				utils_for_wildcard(filename, dir, token, new);
				free(filename);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
