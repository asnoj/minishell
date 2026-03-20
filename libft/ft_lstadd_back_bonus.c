/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:14:38 by aronnet           #+#    #+#             */
/*   Updated: 2026/02/10 21:00:23 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	ft_lstadd_back(t_list **lst, t_list *new)
//{
//	t_list	*current;
//	t_list	*temp;

//	if (*lst == NULL)
//	{
//		*lst = new;
//		return ;
//	}
//	current = *lst;
//	while (current->next->next != NULL)
//		current = current->next;
//	temp = current->next;
//	printf("%s\n", (char *)temp->content);
//	current->next = new;
//	current->next->next = temp;
//}

// int main()
//{
//	t_list *mylist = NULL;
//	t_list *new = "caca";
//	t_list *cac = "pipi";
//	t_list *coc = "fesse";

//	ft_lstadd_front(&mylist, new);
//	ft_lstadd_front(&mylist, cac);

//	ft_lstadd_back(&mylist, coc);
//	puts(mylist->content);
//	puts(mylist->next->content);
//	puts(mylist->next->next->content);
//}
