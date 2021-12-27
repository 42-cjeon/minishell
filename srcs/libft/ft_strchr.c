/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:05:03 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/10 19:05:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	find_char;

	find_char = (char)c;
	while (*s != '\0')
	{
		if (*s == find_char)
			return ((char *)s);
		s++;
	}
	if (find_char == '\0')
		return ((char *)s);
	return (NULL);
}
