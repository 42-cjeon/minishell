/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:13:17 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/13 16:19:16 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*ucs1;
	const unsigned char	*ucs2;
	size_t				index;

	ucs1 = (const unsigned char *)s1;
	ucs2 = (const unsigned char *)s2;
	index = 0;
	while ((ucs1[index] != '\0') && (ucs2[index] != '\0'))
	{
		if (ucs1[index] != ucs2[index])
			break ;
		++index;
	}
	return (ucs1[index] - ucs2[index]);
}
