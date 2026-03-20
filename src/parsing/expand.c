/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 00:00:00 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 18:11:37 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_dollar(char *str, char **result, int exit_signal)
{
	char	*tmp;

	if (str[1] == '$')
	{
		tmp = ft_itoa(getpid());
		if (tmp)
		{
			*result = ft_strjoin(*result, tmp);
			free(tmp);
		}
		return (2);
	}
	if (str[1] == '?')
	{
		tmp = ft_itoa(exit_signal);
		if (tmp)
		{
			*result = ft_strjoin(*result, tmp);
			free(tmp);
		}
		return (2);
	}
	return (0);
}

static int	handle_var_dollar(char *str, char **result, t_list *env)
{
	char	*var_name;
	char	*var_ptr;
	int		var_len;

	if (str[1] && is_valid_var_start(str[1]))
	{
		var_len = get_var_name_len(&str[1]);
		var_name = ft_substr(str, 1, var_len);
		var_ptr = get_env_ptr(var_name, env);
		if (var_ptr)
			*result = ft_strjoin(*result, var_ptr);
		free(var_name);
		return (1 + var_len);
	}
	*result = add_char_to_str(*result, '$');
	return (1);
}

int	handle_dollar(char *str, char **result, t_list *env, int exit_signal)
{
	int	ret;

	ret = handle_special_dollar(str, result, exit_signal);
	if (ret > 0)
		return (ret);
	return (handle_var_dollar(str, result, env));
}

int	is_quote_char(int state, char c)
{
	if (state == STATE_NORMAL && c == '\'')
		return (1);
	if (state == STATE_NORMAL && c == '"')
		return (1);
	if (state == STATE_IN_SINGLE_QUOTE && c == '\'')
		return (1);
	if (state == STATE_IN_DOUBLE_QUOTE && c == '"')
		return (1);
	return (0);
}

char	*expand_token_content(char *str, t_list *env, int exit_signal)
{
	char	*result;
	int		i;
	int		state;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	state = STATE_NORMAL;
	while (str[i])
	{
		if (is_quote_char(state, str[i]))
		{
			update_state_extand(&state, str[i]);
			i++;
			continue ;
		}
		if (!str[i])
			break ;
		if (str[i] == '$' && state != STATE_IN_SINGLE_QUOTE)
			i += handle_dollar(str + i, &result, env, exit_signal);
		else
			result = add_char_to_str(result, str[i++]);
	}
	return (result);
}
