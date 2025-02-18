/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:18 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:18:46 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_first_position(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_in_set(str[i], set))
		i++;
	return (i);
}

static int	ft_last_position(const char *str, const char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_is_in_set(str[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s, const char *set)
{
	int		len;
	char	*str;
	int		i;
	int		start;
	int		end;

	if (!s || !set)
		return (NULL);
	start = ft_first_position(s, set);
	end = ft_last_position(s, set);
	if (start > end)
		return (ft_strdup(""));
	len = end - start + 1;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	const char s[] = " Hello, world! ";
	const char *set = " Hello,world!";
	char *result = ft_strtrim(s, set);
	if (result == NULL)
		printf("Returned null");
	else
	{
		printf("%s\n", result);
		free(result);
	}
	return (0);
}
*/
