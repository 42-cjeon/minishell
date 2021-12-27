/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:10:16 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/10 19:13:18 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*s1 != '\0' && *s1 == *s2 && i + 1 < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (*(unsigned char *)s1 > *(unsigned char *)s2)
		return (1);
	else if (*(unsigned char *)s1 < *(unsigned char *)s2)
		return (-1);
	else
		return (0);
}
