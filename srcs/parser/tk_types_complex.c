/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types_complex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:11:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 09:54:15 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"
#include "tokenizer.h"

t_bool	tk_isstringtype(int type)
{
	return (type == TK_QUOTED_STRING \
			|| type == TK_DQUOTED_STRING \
			|| type == TK_UNESCAPED_STRING);
}

t_bool tk_isredir(int type)
{
	return (type == TK_HEREDOC || type == TK_REDIR_INPUT
		|| type == TK_REDIR_OUTPUT || type == TK_APPEND);
}

t_bool tk_islogicaloper(int type)
{
	return (type == TK_AND || type == TK_OR);
}