/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:29:50 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 18:09:22 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*str;
	int		i;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(total_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	char const	s1[] = "Hello ";
	char const	s2[] = "World!";
	char	*result = ft_strjoin(s1, s2);
	if (result != NULL)
	{
		printf("%s", result);
		free(result);
	}
	return (0);
}
*/
