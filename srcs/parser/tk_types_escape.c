/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:10:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:34:41 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"

t_bool	tk_isspace(const char c)
{
	return (c == ' ' || c == '\t');
}

t_bool	tk_isquote(const char c)
{
	return (c == '\'');
}

t_bool	tk_isdquote(const char c)
{
	return (c == '"');
}

t_bool	tk_isnul(const char c)
{
	return (c == '\0');
}
