/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 08:38:03 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/17 19:49:21 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmpp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n - 1 > i && (str1[i] || str2[i]))
	{
		if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

char	*free_malloc(char *str)
{
	free(str);
	perror("malloc error");
	return (NULL);
}

char	*ft_join_all(char *full_path, char **path_dirs, char *cmd_name, int i)
{
	full_path[0] = '\0';
	full_path = ft_strjoin(full_path, path_dirs[i]);
	full_path = ft_strjoin(full_path, "/");
	full_path = ft_strjoin(full_path, cmd_name);
	return (full_path);
}

void	error_fuction(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(EXIT_FAILURE);
}
