/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:48:31 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:12:10 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		value;

	p = (const unsigned char *)s;
	value = (unsigned char)c;
	while (n > 0)
	{
		if (*p == value)
			return ((void *)p);
		p++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char buffer[] = "Hello, world!";
	char ch = 'a';
	char *result = ft_memchr(buffer, ch, sizeof(buffer));
	printf("%s", result);
	return (0);
}
*/
