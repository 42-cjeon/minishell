/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:20:05 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 08:39:29 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tk_types.h"

t_bool	tk_isdollarsign(const char c)
{
	return (c == '$');
}

t_bool	tk_isidentifier(const char c)
{
	return (ft_isalnum((int)c) || c == '_');
}
