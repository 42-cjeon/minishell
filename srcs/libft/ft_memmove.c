/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:06:40 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/24 19:10:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
	{
		d = (unsigned char *)dst + len - 1;
		s = (const unsigned char *)src + len - 1;
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}
