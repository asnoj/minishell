/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:39:13 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:14:44 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_utils(char *str)
{
	write(2, "export: not a valid identifier\n", 31);
	free(str);
	return (NULL);
}

int	export_skip_to_space(int i, t_token *token)
{
	while (token->command[i])
	{
		if (token->command[i] == ' ')
			break ;
		i++;
	}
	return (i);
}
