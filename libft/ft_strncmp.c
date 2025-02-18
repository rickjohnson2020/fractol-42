/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:06:16 by riyano            #+#    #+#             */
/*   Updated: 2024/12/09 12:16:18 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = "apple";
	char str2[] = "apole";

	printf("%d %d\n", ft_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
	printf("%d %d\n", ft_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
	printf("%d %d\n", ft_strncmp(str1, str2, 2), strncmp(str1, str2, 2));
	printf("%d %d\n", ft_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
	printf("%d %d\n", ft_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
	printf("%d %d\n", ft_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
	printf("%d %d\n", ft_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
	printf("%d %d\n", ft_strncmp(str1, str2, 7), strncmp(str1, str2, 7));

	return 0;
}
*/
