/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:24:36 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 17:24:20 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

int	ft_close(int fildes)
{
	int	result;

	result = close(fildes);
	if (result)
		ft_perror_texit(PROJECT_NAME, 1);
	return (result);
}
