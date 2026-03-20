/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:56:35 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 23:08:06 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(t_token *token, t_token_info *token_info)
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

void	cmd_env(t_token *cmd)
{
	t_list	*envptr;

	envptr = cmd->env;
	while (envptr)
	{
		if (ft_strchr((char *)envptr->content, '='))
			printf("%s\n", (char *)envptr->content);
		envptr = envptr->next;
	}
}
