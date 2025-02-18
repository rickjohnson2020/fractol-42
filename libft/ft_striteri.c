/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:48:04 by riyano            #+#    #+#             */
/*   Updated: 2024/12/06 13:07:37 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include "./libft.h"
#include <strddef.h>
#include <stdio.h>
void	fttoupper(unsigned int idx, char *s)
{
	if (idx >= 0)
	{
		size_t len = ft_strlen(s);
		size_t i = 0;
		while (i < len)
		{
			if (s[i] >= 97 && s[i] <= 122)
				s[i] = s[i] - 32;
			i++;
		}
	}
}

int main()
{
	char s[] = "hello";
	ft_striteri(s, &fttoupper);

	int i = 0;
	while (s[i])
		printf("%c\n", s[i++]);
	return (0);
}
*/
