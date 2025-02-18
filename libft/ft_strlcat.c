/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:27:36 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 18:10:59 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "./libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	size_t	j;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	j = 0;
	if (size <= d_len)
		return (size + s_len);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (d_len + s_len);
}
/*
#include <stdio.h>
int	main(void)
{
	char str1[] = "Hello, ";
	const char str2[] = "World!";
	printf("%zu\n", ft_strlcat(str1, str2, 5));
	printf("%s\n", str1);

	return (0);
}
*/
