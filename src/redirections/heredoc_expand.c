/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:00:00 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 02:18:27 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *str, t_list *env, int exit_signal)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (is_valid_var_start(str[i + 1]) || str[i + 1] == '?'
				|| str[i + 1] == '$'))
			i += handle_dollar(str + i, &result, env, exit_signal);
		else
			result = add_char_to_str(result, str[i++]);
	}
	return (result);
}
