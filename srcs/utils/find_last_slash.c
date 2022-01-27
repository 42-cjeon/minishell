/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 07:57:50 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:40:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "tk_types.h"

t_bool	find_last_slash(const char *path, size_t *last_slash, size_t *len)
{
	size_t	i;
	size_t	last_found;
	t_bool	found;

	found = FALSE;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			found = TRUE;
			last_found = i;
		}		
		i++;
	}
	*len = i;
	if (found)
		*last_slash = last_found;
	return (found);
}
