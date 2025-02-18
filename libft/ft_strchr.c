/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:17:10 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:16:00 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = (unsigned int)c;
	while (*s)
	{
		if ((unsigned char)*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	const char s[] = "Hello, \xFF world!";
	int	c = 0xFF;
	char *str = ft_strchr(s, c);
	printf("%s", str);
	return 0;
}
*/
