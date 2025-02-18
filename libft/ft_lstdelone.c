/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:19:06 by riyano            #+#    #+#             */
/*   Updated: 2024/12/08 15:29:40 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
#include <string.h>
void	del_content(void *content)
{
	free(content);
}

int	main()
{
	char *str = strdup("Hello, world!");
	if (!str)
		return (1);
	t_list	*node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		return (1);
	}
	printf("Before: %s\n", (char *)node->content);
	ft_lstdelone(node, del_content);
	//printf("After: %s\n", (char *)node->content);
	return 0;
}
*/
