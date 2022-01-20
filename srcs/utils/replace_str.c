/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 07:55:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 07:55:39 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_replace_str(char *str, size_t start, size_t len, char *replace_with)
{
	char *result;
	size_t	str_length;
	size_t	with_length;

	str_length = ft_strlen(str);
	with_length = 0;
	if (replace_with != NULL)
		with_length = ft_strlen(replace_with);
	result = ft_malloc(sizeof(char) * (str_length + with_length - len + 1));
	ft_strlcpy(result, str, start + 1);
	if (replace_with != NULL)
		ft_strlcpy(result + start, replace_with, with_length + 1);
	ft_strlcpy(result + start + with_length, str + start + len, \
				str_length - len - start + 1);
	return (result);
}