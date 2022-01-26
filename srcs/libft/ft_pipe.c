/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:27:32 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 17:25:16 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

int	ft_pipe(int fildes[2])
{
	int	result;

	result = pipe(fildes);
	if (result)
		ft_perror_texit(PROJECT_NAME, 1);
	return (result);
}
