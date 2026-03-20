/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:22:53 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 13:46:41 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	if (lst == NULL)
		return ;
	while (current != NULL)
	{
		temp = current->next;
		if (del)
			del(current->content);
		free(current);
		current = temp;
	}
	*lst = NULL;
}

//void	del(void *content)
//{
//	free(content);
//}

//int	main(void)
//{
//	t_list	*list;
//	t_list	*node1;
//	t_list	*node2;
//	t_list	*node3;

//	node1 = ft_lstnew(strdup("Hello"));
//	node2 = ft_lstnew(strdup("World"));
//	node3 = ft_lstnew(strdup("!"));

//	node1->next = node2;
//	node2->next = node3;
//	list = node1;

//	puts(list->content);
//	puts(list->next->content);
//	puts(list->next->next->content);
//	ft_lstclear(&list, del);

//	if (list == NULL)
//		printf("test reussis");
//	return (0);
//}
