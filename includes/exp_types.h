/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:21:48 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 00:38:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_TYPES_H
# define EXP_TYPES_H

# include "ft_types.h"

typedef t_typecmp t_exp_typecmp;

t_bool	exp_isidentifier(const char c);
t_bool	exp_isdollarsign(const char c);

#endif