/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:59:54 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/26 20:50:10 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TK_TYPES_H
# define TK_TYPES_H

# include "ft_types.h"

typedef t_typecmp t_tk_typecmp;

t_bool	tk_isspace(const char c);
t_bool	tk_isquote(const char c);
t_bool	tk_isdquote(const char c);
t_bool	tk_isnul(const char c);
t_bool	tk_isoperator(const char c);
t_bool	tk_iswildcard(const char c);
t_bool	tk_issubshellstart(const char c);
t_bool	tk_issubshellend(const char c);
t_bool	tk_isspacialchar(const char c);

#endif