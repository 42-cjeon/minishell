/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:59:54 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 09:54:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TK_TYPES_H
# define TK_TYPES_H

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef t_bool (*t_typecmp)(const char c);

t_bool	tk_isspace(const char c);
t_bool	tk_isquote(const char c);
t_bool	tk_isdquote(const char c);
t_bool	tk_isnul(const char c);
t_bool	tk_isoperator(const char c);
t_bool	tk_iswildcard(const char c);
t_bool	tk_issubshellstart(const char c);
t_bool	tk_issubshellend(const char c);
t_bool	tk_isspacialchar(const char c);
t_bool	tk_isidentifier(const char c);
t_bool	tk_isdollarsign(const char c);
t_bool	tk_isstringtype(int type);
t_bool	tk_isredir(int type);
t_bool	tk_islogicaloper(int type);

#endif