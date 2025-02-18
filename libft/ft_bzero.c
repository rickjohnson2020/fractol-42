/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:27:33 by riyano            #+#    #+#             */
/*   Updated: 2024/12/04 19:45:52 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
int		main()
{
	char	buffer[10];
	ft_bzero(buffer, sizeof(buffer));

	int		i = 0;
	while (i < sizeof(buffer))
	{
		printf("%d", buffer[i]);
		i++;
	}
	return (0);
}
*/
