/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:46:47 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 09:55:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "tk_types.h"
#include "tokenizer.h"

t_bool	context_peek_cmp(t_tokenizer_context *context, t_typecmp tk_typecmp)
{
	return (tk_typecmp(context->raw_line[context->cursor]));
}

size_t	seek_first_nq(t_tokenizer_context *context, t_typecmp tk_typecmp)
{
	size_t	i;

	i = 0;
	while (!context_peek_cmp(context, tk_isnul) \
			&& context_peek_cmp(context, tk_typecmp))
	{
		i++;
		context->cursor++;
	}
	return (i);
}

size_t	seek_first_eq(t_tokenizer_context *context, t_typecmp tk_typecmp)
{
	size_t	i;

	i = 0;
	while (!context_peek_cmp(context, tk_isnul) \
			&& !context_peek_cmp(context, tk_typecmp))
	{
		i++;
		context->cursor++;
	}
	return (i);
}

size_t	seek_first_nq_op(t_tokenizer_context *context)
{
	size_t	i;
	char	first_op;

	first_op = context->raw_line[context->cursor++];
	i = 1;
	while (first_op == context->raw_line[context->cursor])
	{
		i++;
		context->cursor++;
	}
	return (i);
}