/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:27:56 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:19:07 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_info	*init_token_main(t_token_info *tokens, char *line,
		int *exit_signal, t_list **env)
{
	t_token	tmp_token;

	tmp_token.command = NULL;
	tmp_token.args = NULL;
	tmp_token.args_i = 0;
	tmp_token.skip = 0;
	tmp_token.redirects = NULL;
	tmp_token.next = NULL;
	tmp_token.exit_signal = exit_signal;
	tmp_token.env = *env;
	tokens = strs_tokenizer(line, &tmp_token);
	return (tokens);
}

int	free_everythings(t_token *commands, t_token **temp)
{
	if (commands->command && ft_strncmpp(commands->command, "exit", 4) == 0)
	{
		free_token_list(*temp);
		return (-1);
	}
	free_token_list(*temp);
	return (0);
}

int	process_line(char *line, char **envp, t_list **env, int *exit_signal)
{
	t_token_info	*tokens;
	t_token			*commands;
	t_token			**temp;

	tokens = init_token_main(tokens, line, exit_signal, env);
	if (!tokens)
		return (0);
	if (!is_valid_syntax(tokens))
	{
		free_tokens(tokens);
		*exit_signal = 2;
		return (0);
	}
	commands = fill_struct(tokens, envp);
	clean_all_redirects(commands);
	if (commands)
	{
		update_all_tokens_env(commands, *env);
		free_tokens(tokens);
		temp = &commands;
		*exit_signal = verif_command(commands);
		*env = commands->env;
	}
	return (free_everythings(commands, temp));
}

int	turn_line(char *line, t_list *env, char **envp, int exit_signal)
{
	while (1)
	{
		g_signal = 0;
		line = readline("minishell> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		g_signal = 0;
		if (process_line(line, envp, &env, &exit_signal) == -1)
			break ;
		free(line);
	}
	free_env_list(env);
	return (exit_signal);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tmp;
	t_list	*env;
	int		exit_signal;

	(void)ac;
	(void)av;
	exit_signal = 0;
	tmp = new_token();
	fill_env(tmp, envp);
	env = tmp->env;
	free_token_list(tmp);
	setup_signals_interactive();
	turn_line(line, env, envp, exit_signal);
	rl_clear_history();
	return (0);
}
