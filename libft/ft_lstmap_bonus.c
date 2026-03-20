/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:30:56 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 14:13:32 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

//void	**f(void *s)
//{
//	s;
//}

//void	del(void *content)
//{
//	free(content);
//}

//int	main(void)
//{
//	t_list *list;
//	t_list *mapped;
//	t_list *tmp;

//	list = ft_lstnew(strdup("hello"));
//	list->next = ft_lstnew(strdup("world"));
//	list->next->next = ft_lstnew(strdup("test"));
//	mapped = ft_lstmap(list, f, del);
//	tmp = mapped;
//	puts (tmp->content);
//	return (0);
//}