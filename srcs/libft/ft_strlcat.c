/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:12:13 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/11 15:23:13 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;

	dst_len = 0;
	while (*dst != '\0' && dst_len < dstsize)
	{
		dst++;
		dst_len++;
	}
	if (dst_len == dstsize)
		return (dst_len + ft_strlen(src));
	return (dst_len + ft_strlcpy(dst, src, dstsize - dst_len));
}
