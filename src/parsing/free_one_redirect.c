/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_one_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:46:02 by jcrochet          #+#    #+#             */
/*   Updated: 2026/03/17 21:48:35 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_file_creation(t_redirect *redir)
{
	int	fd;

	if (!redir->file || ft_strncmpp(redir->file, "NONE", 4) == 0)
		return ;
	if (redir->type == REDIRECT_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIRECT_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return ;
	if (fd >= 0)
		close(fd);
}

static void	free_wild_list(t_list *wild)
{
	t_list	*tmp;

	while (wild)
	{
		tmp = wild->next;
		free(wild->content);
		free(wild);
		wild = tmp;
	}
}

void	free_one_redirect(t_redirect *redir)
{
	if (!redir)
		return ;
	handle_file_creation(redir);
	free_wild_list(redir->wild);
	if (redir->file)
		free(redir->file);
	free(redir);
}
