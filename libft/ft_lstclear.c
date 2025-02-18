/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:37:51 by riyano            #+#    #+#             */
/*   Updated: 2024/12/08 15:01:06 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
void	del_content(void *content)
{
	free(content);
}

#include <stdio.h>
#include <string.h>
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
	char *str0 = strdup("Node 0");
	char *str1 = strdup("Node 1");
	ft_lstadd_back(&list, ft_lstnew(str0));
	print_list(list);

	ft_lstadd_back(&list, ft_lstnew(str1));
	print_list(list);

	ft_lstclear(&list, del_content);
	print_list(list);
	return 0;
}
*/
