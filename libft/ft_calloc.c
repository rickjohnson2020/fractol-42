/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:42:42 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:09:47 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			total_size;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < total_size)
		p[i++] = 0;
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*array;
	size_t elements = 5;
	array = (int *)ft_calloc(elements, sizeof(int));
	if (array == NULL)
		return (1);
	size_t i = 0;
	while (i < elements)
		printf("%d", array[i++]);
	return (0);
}
*/
