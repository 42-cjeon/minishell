/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:32:47 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/11 15:18:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	while (*src != '\0')
	{
		if (len + 1 < dstsize)
		{
			*dst = *src;
			dst++;
		}
		src++;
		len++;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (len);
}
