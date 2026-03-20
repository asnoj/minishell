/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuction_for_cd2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 00:00:00 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/17 16:55:14 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cd_vars(t_token *token, char ***str, char **strs, char **path)
{
	*str = ft_split(token->command, ' ');
	*strs = ft_pwd(token);
	*path = NULL;
}

static int	cd_home(char *test, char **str)
{
	char	**ts;
	char	*path;

	ts = NULL;
	path = NULL;
	if (test != NULL)
	{
		ts = ft_split(test, '/');
		path = return_path(ts);
	}
	if (test == NULL || path == NULL || chdir(path) == -1)
	{
		if (test == NULL)
			printf("HOME is unset\n");
		else
			perror("cd");
		return (free_split(str), free_split(ts), free(path), 0);
	}
	free_split(ts);
	free(path);
	return (1);
}

static void	cd_update_oldpwd(t_token *token, char *strs)
{
	pwd_actu(token);
	free(token->command);
	token->command = ft_strdup("export OLDPWD=");
	token->command = ft_strjoin(token->command, strs);
	free(strs);
	ft_export(token);
}

static int	cd_dispatch(t_token *token, char **str, int *n)
{
	char	*test;

	test = get_env_ptr("HOME", token->env);
	if (!str[1])
		return (cd_home(test, str));
	else if (ft_strncmp(str[1], "-", 1) == 0)
		*n = cd_old(token);
	else
		*n = cd_nrml(str[1]);
	return (*n);
}

int	builtin_cd(t_token *token)
{
	char	**str;
	char	*strs;
	char	*path;
	int		n;

	n = 1;
	init_cd_vars(token, &str, &strs, &path);
	if (!cd_dispatch(token, str, &n))
	{
		free(strs);
		free_split(str);
		return (0);
	}
	free_split(str);
	cd_update_oldpwd(token, strs);
	return (n);
}
