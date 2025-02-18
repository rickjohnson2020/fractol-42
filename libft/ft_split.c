/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:59:43 by riyano            #+#    #+#             */
/*   Updated: 2024/12/05 20:15:45 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_words(char const *str, char delimiter)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == delimiter)
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		str++;
	}
	return (count);
}

static char	*ft_copy_word(char const *start, char const *end)
{
	int		len;
	int		i;
	char	*word;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_split_word(char **result, char const *str, char delimiter)
{
	char const	*word_start;
	int			i;

	word_start = NULL;
	i = 0;
	while (*str)
	{
		if (*str == delimiter)
		{
			if (word_start)
			{
				result[i++] = ft_copy_word(word_start, str);
				word_start = NULL;
			}
		}
		else if (!word_start)
			word_start = str;
		str++;
	}
	if (word_start)
		result[i++] = ft_copy_word(word_start, str);
	result[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	word_count = ft_count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	ft_split_word(result, s, c);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char const	str[] = "Hello, world 42 ! oij";
	char delimiter = ' ';
	char **result = ft_split(str, delimiter);

	int	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		//free(result[i]);
		i++;
	}
	free(result);

	return (0);
}
*/
