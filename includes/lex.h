/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 05:29:55 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/07 05:23:55 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

#include "tokenize.h"

enum e_lexer_result
{
	LEX_SUCCESS,
	LEX_EUNKNOWN_OPER
};

int lex(t_tokenv *tokenv);

#endif