/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:01 by riyano            #+#    #+#             */
/*   Updated: 2024/12/06 13:05:19 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	size_t			len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char fttoupper(unsigned int idx, char c)
{
	if (idx >= 0)
	{
		if (c >= 97 && c <= 122)
			c -= 32;
	}
	return (c);
}

#include <stdio.h>
int	main()
{
	char const s[] = "Hello";
	char *result = ft_strmapi(s, &fttoupper);

	int i = 0;
	while (result[i])
		printf("%c\n", result[i++]);
	free(result);
	return (0);
}
*/
