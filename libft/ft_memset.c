/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:51:38 by riyano            #+#    #+#             */
/*   Updated: 2024/12/09 13:17:36 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int		main()
{
	char	buffer[10];
	ft_memset(buffer, 'B', sizeof(buffer));

	size_t	i = 0;
	while (i < sizeof(buffer))
	{
		printf("%c", buffer[i]);
		i++;
	}
	return (0);
}
*/
