/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuction_for_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:30:01 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/14 02:31:11 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_old(t_token *token)
{
	t_list	*lst;

	lst = token->env;
	while (lst != NULL)
	{
		if (ft_strncmpp(lst->content, "OLDPWD", 6) == 0)
			break ;
		lst = lst->next;
	}
	if (lst == NULL)
	{
		printf("cd : OLDPWD not set\n");
		return (0);
	}
	if (chdir((char *)&lst->content[7]) == -1)
	{
		perror("error with cd");
		return (0);
	}
	return (1);
}

char	*return_path(char **str)
{
	int		len;
	char	*path;
	int		j;

	if (str[1] == NULL)
		return (NULL);
	len = ft_strlen(str[0]) + ft_strlen(str[1]) + 3;
	path = malloc(len);
	if (!path)
		return (NULL);
	path[0] = '/';
	j = ft_strlen(str[0]);
	ft_strlcpy(&path[1], str[0], j + 1);
	path[1 + j] = '/';
	ft_strlcpy(&path[2 + j], str[1], ft_strlen(str[1]) + 1);
	return (path);
}

int	cd_nrml(char *str)
{
	if (chdir(str) == -1)
	{
		perror("error with cd");
		return (0);
	}
	return (1);
}

void	pwd_actu(t_token *token)
{
	char	*strs;

	strs = ft_pwd(token);
	free(token->command);
	token->command = ft_strdup("export PWD=");
	token->command = ft_strjoin(token->command, strs);
	free(strs);
	ft_export(token);
}

void	free_split(char **str)
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
