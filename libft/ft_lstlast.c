/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:54:21 by riyano            #+#    #+#             */
/*   Updated: 2024/12/06 18:15:31 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
int	main()
{
	t_list *list = NULL;
	t_list *list_last = NULL;
	ft_lstadd_front(&list, ft_lstnew("Node 2"));
	ft_lstadd_front(&list, ft_lstnew("Node 1"));
	ft_lstadd_front(&list, ft_lstnew("Node 0"));
	list_last = ft_lstlast(list);
	printf("%s\n", (char *)list_last->content);
	return (0);
}
*/
