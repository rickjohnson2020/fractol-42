/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:08:41 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 18:11:29 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	const char		*pointer;

	pointer = 0;
	ch = (unsigned int)c;
	while (*s)
	{
		if ((unsigned char)*s == ch)
			pointer = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)pointer);
}
/*
#include <stdio.h>
int	main(void)
{
	const char s[] = "Hello, \xFF world!";
	int c = '\0';
	char *result = ft_strrchr(s, c);
	if (result == NULL)
		printf("Returned NULL pointer\n");
	else
	{
		printf("%s\n", result);
		printf("%ld\n", result - s);
	}

	return 0;
}
*/
