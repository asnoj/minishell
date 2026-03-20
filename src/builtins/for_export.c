/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:51:55 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/18 23:12:41 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	return (name);
}

static char	**fill_arr(t_token *cmd, int size)
{
	char	**arr;
	t_list	*env;
	int		i;

	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	env = cmd->env;
	i = 0;
	while (env)
	{
		arr[i++] = get_var_name((char *)env->content);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_arr(char **arr, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_arr(t_token *cmd, char **arr, int size)
{
	t_list	*env;
	int		i;

	i = 0;
	while (i < size)
	{
		env = cmd->env;
		while (env)
		{
			if (ft_strncmpp((char *)env->content, arr[i],
					ft_strlen(arr[i])) == 0)
				printf("declare -x %s\n", (char *)env->content);
			env = env->next;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_for_export(t_token *cmd)
{
	char	**arr;
	int		size;

	size = ft_lstsize(cmd->env);
	arr = fill_arr(cmd, size);
	if (!arr)
		return ;
	sort_arr(arr, size);
	print_arr(cmd, arr, size);
}
