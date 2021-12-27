/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:37:23 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/13 23:57:56 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_array(char **array, size_t max_index)
{
	while (max_index--)
		free(array[max_index]);
	free(array);
}

static int	append_array(char **array, size_t index,
						const char *start, size_t len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		free_array(array, index);
		return (0);
	}
	ft_strlcpy(str, start, len + 1);
	array[index] = str;
	return (1);
}

static int	parse_string(char **array, const char *str, char c)
{
	const char	*word_start;
	size_t		word_len;
	size_t		index;

	index = 0;
	while (c != '\0' && *str == c)
		str++;
	while (*str != '\0')
	{
		word_start = str;
		word_len = 0;
		while (*str != c && *str != '\0')
		{
			word_len++;
			str++;
		}
		if (!append_array(array, index, word_start, word_len))
			return (0);
		index++;
		while (c != '\0' && *str == c)
			str++;
	}
	array[index] = NULL;
	return (1);
}

static char	**get_empty_array(const char *str, char c)
{
	int		was_split_char;
	char	**array;
	size_t	arr_len;

	arr_len = 0;
	was_split_char = 1;
	while (*str)
	{
		if (c == *str)
			was_split_char = 1;
		else
		{
			if (was_split_char)
				arr_len++;
			was_split_char = 0;
		}
		str++;
	}
	array = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (array == NULL)
		return (NULL);
	return (array);
}

char	**ft_split(const char *str, char c)
{
	char	**array_of_strings;

	array_of_strings = get_empty_array(str, c);
	if (array_of_strings == NULL)
		return (NULL);
	if (!parse_string(array_of_strings, str, c))
		return (NULL);
	return (array_of_strings);
}
