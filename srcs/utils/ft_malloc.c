/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 20:34:39 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/13 22:06:11 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		ft_perror_texit("minishell", 1);
	return (ret);
}
