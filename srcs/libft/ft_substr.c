/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:19:06 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 17:23:33 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	result_length;

	result_length = ft_strlen(s);
	if (result_length <= start)
	{
		str = (char *)ft_malloc(sizeof(char) * (1));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	s += start;
	if (len < result_length)
		result_length = len;
	str = (char *)ft_malloc(sizeof(char) * (result_length + 1) * 2);
	if (str == NULL)
		return (NULL);
	str[result_length] = '\0';
	while (result_length--)
		str[result_length] = s[result_length];
	return (str);
}
