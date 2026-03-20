/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:06:01 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/03 14:13:50 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_nodle;

	new_nodle = malloc(1 * sizeof(t_list));
	if (!new_nodle)
		return (NULL);
	new_nodle->content = ft_strdup((char *)content);
	new_nodle->next = NULL;
	return (new_nodle);
}

//int	main(void)
//{
//	t_list	*mylist;

//	mylist = ft_lstnew("caca");
//	puts(mylist->content);
//	return (0);
//}
