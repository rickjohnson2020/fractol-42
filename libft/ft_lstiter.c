/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:14:28 by riyano            #+#    #+#             */
/*   Updated: 2024/12/08 18:52:41 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	fttoupper(void *s)
{
	char *str = (char *)s;
	size_t len = ft_strlen(str);
	size_t i = 0;
	while (i < len)
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
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
	t_list *list = NULL;
	ft_lstadd_front(&list, ft_lstnew(strdup("Node 1")));
	ft_lstadd_front(&list, ft_lstnew(strdup("Node 0")));
	print_list(list);
	ft_lstiter(list, &fttoupper);
	print_list(list);
	return 0;
}
*/
