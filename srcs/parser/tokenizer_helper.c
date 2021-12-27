/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:46:47 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 15:20:33 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tokenize.h"
#include "tk_types.h"

t_bool	context_peek_cmp(t_tokenizer_context *context, \
							t_tk_typecmp tk_typecmp)
{
	return (tk_typecmp(context->raw_line[context->cursor]));
}

size_t	seek_first_nq(t_tokenizer_context *context, t_tk_typecmp tk_typecmp)
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

size_t	seek_first_eq(t_tokenizer_context *context, t_tk_typecmp tk_typecmp)
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