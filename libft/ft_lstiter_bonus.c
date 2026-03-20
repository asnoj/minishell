/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:27:58 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 15:19:40 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

//void	f(void *content)
//{
//	printf("%s\n", (char *)content);
//}

//int	main(void)
//{
//	t_list	*list;

//	list = ft_lstnew("Hello");
//	list->next = ft_lstnew("World");
//	list->next->next = ft_lstnew("!");

//	ft_lstiter(list, f);
//	return (0);
//}
