/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:20:34 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 19:22:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*is_output_input(t_inout inout, t_token *token)
{
	t_redirect	*current;

	if (!token || !token->redirects)
		return (NULL);
	current = token->redirects;
	if (inout == OUTPUT)
	{
		while (current)
		{
			if (current->type == REDIRECT_APPEND
				|| current->type == REDIRECT_OUT)
				return (current->file);
			current = current->next;
		}
		return (NULL);
	}
	while (current)
	{
		if (current->type == REDIRECT_HEREDOC
			|| current->type == REDIRECT_IN)
			return (current->file);
		current = current->next;
	}
	return (NULL);
}

int	is_output_input_pipe(t_inout inout, t_token *token)
{
	t_redirect	*current;

	if (!token || !token->redirects)
		return (0);
	current = token->redirects;
	if (inout == OUTPUT)
	{
		while (current)
		{
			if (current->type == REDIRECT_PIPE_OUT)
				return (REDIRECT_PIPE_OUT);
			current = current->next;
		}
	}
	else if (inout == INPUT)
	{
		while (current)
		{
			if (current->type == REDIRECT_PIPE_IN)
				return (REDIRECT_PIPE_IN);
			current = current->next;
		}
	}
	return (0);
}
