/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:43:04 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/14 00:23:32 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_to_str(char *temp, int n, int is_neg)
{
	int	start;

	start = 10;
	if (is_neg)
	{
		temp[start--] = '0' - (n % 10);
		n = -(n / 10);
	}
	else
	{
		temp[start--] = n % 10 + '0';
		n /= 10;
	}
	while (n)
	{
		temp[start--] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg)
		temp[start--] = '-';
	return (start + 1);
}

char	*ft_itoa(int n)
{
	char	temp[12];
	int		is_neg;
	int		start;

	temp[11] = '\0';
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	start = convert_to_str(temp, n, is_neg);
	return (ft_strdup(temp + start));
}
