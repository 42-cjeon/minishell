/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:27:32 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/25 10:30:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_pipe(int fildes[2])
{
	int result;

	result = pipe(fildes);
	if (result)
		ft_perror_texit(PROJECT_NAME, 1);
	return (result);
}