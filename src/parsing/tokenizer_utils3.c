/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:53:44 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 19:09:19 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_ptr(char *var_name, t_list *env)
{
	int		len;
	char	*line;

	if (!var_name || !env)
		return (NULL);
	len = ft_strlen(var_name);
	while (env)
	{
		line = (char *)env->content;
		if (ft_strncmpp(line, var_name, len) == 0 && line[len] == '='
			&& line[len + 1])
			return (&line[len + 1]);
		env = env->next;
	}
	return (NULL);
}

int	get_var_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

t_tokenizer	*init_tok(char *line)
{
	t_tokenizer	*tok;

	tok = malloc(sizeof(t_tokenizer));
	if (!tok)
		return (NULL);
	tok->line = line;
	tok->i = 0;
	tok->tok_count = 0;
	tok->state = STATE_NORMAL;
	tok->current_token = NULL;
	return (tok);
}
