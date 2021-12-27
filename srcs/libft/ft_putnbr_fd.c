/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:35:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/14 00:22:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

void	ft_putnbr_fd(int n, int fd)
{
	char	temp[11];
	int		is_neg;
	int		start;

	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	start = convert_to_str(temp, n, is_neg);
	write(fd, temp + start, 11 - start);
}
