/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 20:34:39 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/09 20:54:25 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_malloc(size_t size)
{
	void	*ret;
	
	ret = malloc(size);
	if (ret == NULL)
		ft_perror_errno_texit("minishell", NULL, 1);
	return (ret);
}
