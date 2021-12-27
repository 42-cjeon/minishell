/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:10:35 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/10 19:13:50 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *heystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	heystack_len;
	size_t	i;
	size_t	j;

	needle_len = ft_strlen(needle);
	heystack_len = ft_strlen(heystack);
	if (heystack_len < needle_len || len < needle_len)
		return (NULL);
	if (len < heystack_len)
		heystack_len = len;
	i = 0;
	while (i <= heystack_len - needle_len)
	{
		j = 0;
		while (j < needle_len && needle[j] == heystack[i + j])
			j++;
		if (j == needle_len)
			return ((char *)heystack + i);
		i++;
	}
	return (NULL);
}
