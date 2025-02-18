/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:20:55 by riyano            #+#    #+#             */
/*   Updated: 2024/12/06 17:49:32 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*
#include <stdio.h>
int	main()
{
	t_list *list = NULL;
	ft_lstadd_front(&list, ft_lstnew("Node 2"));
	ft_lstadd_front(&list, ft_lstnew("Node 1"));
	ft_lstadd_front(&list, ft_lstnew("Node 0"));
	int i = ft_lstsize(list);
	printf("%d\n", i);
	return 0;
}
*/
