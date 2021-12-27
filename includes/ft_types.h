/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:22:46 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 00:38:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOOL_H
# define FT_BOOL_H

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef t_bool (*t_typecmp)(const char c);

#endif