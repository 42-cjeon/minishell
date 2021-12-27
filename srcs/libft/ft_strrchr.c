/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:09:28 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/10 19:14:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		find_char;
	const char	*last_found;

	find_char = (char)c;
	last_found = NULL;
	while (*s != '\0')
	{
		if (*s == find_char)
			last_found = s;
		s++;
	}
	if (find_char == '\0')
		return ((char *)s);
	return ((char *)last_found);
}
