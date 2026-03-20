/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:42:07 by aronnet           #+#    #+#             */
/*   Updated: 2026/02/10 14:08:32 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

//void	del(void *content)
//{
//	free(content);
//}

//int	main(void)
//{
//	t_list	*node;

//	node = ft_lstnew(strdup("Hello"));
//	puts(node->content);

//	printf("ok\n");
//	return (0);
//}
