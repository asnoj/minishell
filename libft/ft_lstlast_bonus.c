/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:19:02 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 15:21:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	t_list	*temp;

	current = lst;
	if (current == NULL)
		return (current);
	while (current->next != NULL)
	{
		temp = current;
		current = current->next;
	}
	return (current);
}

//int	main(void)
//{
//	t_list	*list;
//	t_list	*last;

//	list = ft_lstnew("Premier");
//	list->next = ft_lstnew("Deuxieme");
//	list->next->next = ft_lstnew("Dernier");

//	last = ft_lstlast(list);
//	printf("test Dernier: %s\n", (char *)last->content);

//	printf("test NULL: %p\n", ft_lstlast(NULL));
//	return (0);
//}
