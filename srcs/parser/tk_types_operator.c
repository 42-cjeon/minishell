/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:11:41 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/27 04:22:37 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"

t_bool	tk_isoperator(const char c)
{
	return (c == '&' || c == '|' || c == '<' || c == '>' || c == '<');
}

t_bool	tk_iswildcard(const char c)
{
	return (c == '*');
}

t_bool	tk_issubshellstart(const char c)
{
	return (c == '(');
}

t_bool	tk_issubshellend(const char c)
{
	return (c == ')');
}

t_bool	tk_isspacialchar(const char c)
{
	return (
		tk_isquote(c)
		|| tk_isdquote(c)
		|| tk_isoperator(c)
		|| tk_issubshellstart(c)
		|| tk_issubshellend(c)
		|| tk_isspace(c)
		|| tk_iswildcard(c)
	);
}
