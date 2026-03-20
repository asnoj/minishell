/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:42 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:18:54 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error_numeric(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free(arg);
	return (127);
}

static void	exit_error_numeric_norm(char *arg, t_token *token)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free(arg);
	free_during_pipe(token, NULL, NULL);
	exit(2);
}

int	fast_builtin_exit(char *exit_cmd)
{
	char		*arg_start;
	char		*arg;
	int			nb_args;
	long long	code;

	ft_putstr_fd("exit\n", 2);
	nb_args = count_args(exit_cmd);
	if (nb_args == 1)
		return (0);
	arg_start = get_first_arg(exit_cmd);
	arg = extract_word(arg_start);
	if (!is_numeric(arg) || check_overflow(arg))
		return (exit_error_numeric(arg));
	if (nb_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free(arg);
		return (127);
	}
	code = ft_atoll(arg);
	free(arg);
	return ((unsigned char)code);
}

void	exit_utils(t_token *token)
{
	free_during_pipe(token, NULL, NULL);
	exit(0);
}

int	builtin_exit(t_token *token)
{
	char		*arg_start;
	char		*arg;
	int			nb_args;
	long long	code;

	nb_args = count_args(token->command);
	if (nb_args == 1)
		exit_utils(token);
	arg_start = get_first_arg(token->command);
	arg = extract_word(arg_start);
	if (!is_numeric(arg) || check_overflow(arg))
		exit_error_numeric_norm(arg, token);
	if (nb_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free(arg);
		free_during_pipe(token, NULL, NULL);
		return (1);
	}
	code = ft_atoll(arg);
	free(arg);
	free_during_pipe(token, NULL, NULL);
	exit((unsigned char)code);
	return (0);
}
