/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:54 by riyano            #+#    #+#             */
/*   Updated: 2024/12/09 11:43:37 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_lst;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_lst = ft_lstlast(*lst);
	if (last_lst != NULL)
		last_lst->next = new;
}
/*
#include <stdio.h>
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
int	main()
{
	t_list	*list = NULL;
	ft_lstadd_back(&list, ft_lstnew("Node 0"));
	print_list(list);

	ft_lstadd_back(&list, ft_lstnew("Node 1"));
	print_list(list);
	return 0;
}
*/
