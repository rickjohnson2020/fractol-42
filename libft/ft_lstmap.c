/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:44:38 by riyano            #+#    #+#             */
/*   Updated: 2024/12/08 18:51:48 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <string.h>
#include <stdlib.h>
void	*fttoupper(void *str)
{
	char *s = (char *)str;
	char *new_str = strdup(s);
	if (!new_str)
		return (NULL);
	int i = 0;
	while (new_str[i])
	{
		if (new_str[i] >= 97 && new_str[i] <= 122)
			new_str[i] = new_str[i] - 32;
		i++;
	}
	return new_str;
}

void	del_content(void *content)
{
	free(content);
}

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
	t_list *list = NULL;
	t_list *result = NULL;
	char *s1 = strdup("hello");
	char *s2 = strdup("world");
	ft_lstadd_back(&list, ft_lstnew(s1));
	ft_lstadd_back(&list, ft_lstnew(s2));
	print_list(list);
	result = ft_lstmap(list, fttoupper, del_content);
	print_list(list);
	ft_lstclear(&list, del_content);
	ft_lstclear(&result, del_content);
	return 0;
}
*/
