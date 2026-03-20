/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:16 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 21:35:50 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sigaction_ignore(int sig)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(sig, &sa, NULL);
}

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction_ignore(SIGQUIT);
	sigaction_ignore(SIGPIPE);
}

void	setup_signals_parent(void)
{
	sigaction_ignore(SIGINT);
	signal(SIGPIPE, SIG_IGN);
	sigaction_ignore(SIGQUIT);
	sigaction_ignore(SIGPIPE);
}
