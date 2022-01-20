/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streq.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 03:17:00 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 08:03:56 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"

t_bool streq(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

t_bool streq_part(const char *heystack, const char *needle)
{
	while (*needle != '\0')
		if (*heystack++ != *needle++)
			return (FALSE);
	return (TRUE);
}
