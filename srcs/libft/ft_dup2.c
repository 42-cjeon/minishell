/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:41:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/25 10:26:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

int	ft_dup2(int fildes, int fildes2)
{
	int result;

	result = dup2(fildes, fildes2);
	if (result == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	return (result);
}