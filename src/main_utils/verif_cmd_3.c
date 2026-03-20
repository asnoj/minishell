/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:38:51 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 20:04:29 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_skip_token(int prev_type, int prev_status)
{
	if (prev_type == REDIRECT_AND && prev_status != 0)
		return (1);
	if (prev_type == REDIRECT_OR && prev_status == 0)
		return (1);
	return (0);
}

int	is_output_type(int type)
{
	if (type == REDIRECT_APPEND || type == REDIRECT_OUT)
		return (1);
	if (type == REDIRECT_PIPE_OUT)
		return (1);
	return (0);
}

int	is_none(char *str)
{
	if (!str)
		return (1);
	if (ft_strncmpp(str, "NONE", 4) == 0)
		return (1);
	return (0);
}
