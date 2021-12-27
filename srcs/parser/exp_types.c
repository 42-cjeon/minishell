/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:20:05 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 00:35:33 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exp_types.h"

t_bool	exp_isdollarsign(const char c)
{
	return (c == '$');
}

t_bool	exp_isidentifier(const char c)
{
	return (ft_isalnum((int)c) || c == '_');
}