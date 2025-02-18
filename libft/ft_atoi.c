/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:27:50 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 18:10:07 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(const char c)
{
	int		i;
	char	whitespace[6];

	whitespace[0] = ' ';
	whitespace[1] = '\n';
	whitespace[2] = '\t';
	whitespace[3] = '\v';
	whitespace[4] = '\f';
	whitespace[5] = '\r';
	i = 0;
	while (i < 6)
	{
		if (c == whitespace[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	while (is_whitespace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main()
{
	const char	str[] = " +42abc432";
	int	i = ft_atoi(str);
	int j = atoi(str);
	printf("%d\n%d\n", i, j);
	return 0;
}
*/
