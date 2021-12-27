/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:42:08 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 18:39:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tk_types.h"
#include "exp_types.h"

char *ft_replace_str(char *str, size_t start, size_t len, char *with)
{
	char *result;
	size_t	str_length;
	size_t	with_length;

	str_length = ft_strlen(str);
	with_length = 0;
	if (with != NULL)
		with_length = ft_strlen(with);
	result = malloc(sizeof(char) * (str_length + with_length - len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str, start + 1);
	if (with != NULL)
		ft_strlcpy(result + start, with, with_length + 1);
	ft_strlcpy(result + start + with_length, str + start + len, \
				str_length - len - start + 1);
	return (result);
}

size_t	replace_variable(char **str, const size_t start)
{
	size_t	len;
	char	*varname;
	char	*newstr;

	len = 1;
	while ((*str)[len + start] != '\0' && exp_isidentifier((*str)[len + start]))
		len++;
	if (len == 1)
	{
		if ((*str)[len] == '?')
			return (2); // need implement
		return (1);
	}
	varname = ft_substr(*str, start + 1, len - 1);
	if (varname == NULL)
		return (0);
	newstr = ft_replace_str(*str, start, len, getenv(varname));
	free(varname);
	if (newstr == NULL)
		return (0);
	free(*str);
	*str = newstr;
	return (len);
}