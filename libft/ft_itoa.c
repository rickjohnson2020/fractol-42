/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:28:56 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:11:45 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_num_length(int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, long num, int len, int sign)
{
	str[len] = '\0';
	len--;
	if (num == 0)
		str[len] = '0';
	while (num != 0)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	if (sign)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;
	int		sign;

	num = n;
	len = get_num_length(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		sign = 1;
	}
	else
		sign = 0;
	fill_str(str, num, len, sign);
	return (str);
}
/*
#include <stdio.h>
int	main()
{
	char *result = ft_itoa(-2147483648);
	printf("%s", result);
	return (0);
}
*/
