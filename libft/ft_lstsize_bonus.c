/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:10:29 by aronnet           #+#    #+#             */
/*   Updated: 2025/10/17 13:59:08 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		i;

	current = lst;
	i = 0;
	if (current == NULL)
		return (0);
	while (current->next != NULL)
	{
		current = current->next;
		i++;
	}
	return (i + 1);
}

//int	main(void)
//{
//	t_list	*node1;
//	t_list	*node2;
//	t_list	*node3;

//	node1 = ft_lstnew("1");
//	node2 = ft_lstnew("2");
//	node3 = ft_lstnew("3");

//	node1->next = node2;
//	node2->next = node3;

//	printf("tailles de la liste: %d\n", ft_lstsize(node1));
//	printf("Taille avec test NULL: %d\n", ft_lstsize(NULL));
//	return (0);
//}
