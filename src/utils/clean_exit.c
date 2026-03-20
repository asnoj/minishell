/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:00:00 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/18 02:47:38 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(int code)
{
	char	*num;
	char	*cmd;
	char	*args[4];

	num = ft_itoa(code);
	cmd = ft_strjoin(ft_strdup("exit "), num);
	free(num);
	args[0] = "sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, NULL);
	free(cmd);
	exit(code);
}
