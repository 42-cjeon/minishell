/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:19:27 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/30 09:21:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

int	ft_dup(int fd)
{
	int	new;

	new = dup(fd);
	if (new == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	return (new);
}