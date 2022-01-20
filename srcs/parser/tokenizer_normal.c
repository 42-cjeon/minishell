/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 07:50:13 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:51:07 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"
#include "tokenizer.h"
#include "libft.h"

int	tokenize_unescaped(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = context->cursor++;
	len = seek_first_eq(context, tk_isspacialchar) + 1;
	token = ft_substr(context->raw_line, start, len);
	tokenv_assign_push(context->tokenv, token, TK_UNESCAPED_STRING);
	return (select_next_tokenizer(context));
}

int	tokenize_space(t_tokenizer_context *context)
{
	seek_first_nq(context, tk_isspace);
	tokenv_assign_push(context->tokenv, NULL, TK_SPACE);
	return (select_next_tokenizer(context));
}

int	tokenize_subshell(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = ++context->cursor;
	len = seek_first_eq(context, tk_issubshellend);
	if (context_peek_cmp(context, tk_isnul))
		return (TKZR_EUNEXPECTEDNL);
	context->cursor++;
	token = ft_substr(context->raw_line, start, len);
	tokenv_assign_push(context->tokenv, token, TK_SUBSHELL);
	return (select_next_tokenizer(context));
}

int	tokenize_operator(t_tokenizer_context *context)
{
	size_t	len;
	size_t	start;
	char	*token;

	start = context->cursor;
	len = seek_first_nq_op(context);
	token = ft_substr(context->raw_line, start, len);
	tokenv_assign_push(context->tokenv, token, TK_OPERATOR);
	return (select_next_tokenizer(context));
}

int	tokenize_wildcard(t_tokenizer_context *context)
{
	context->cursor++;
	tokenv_assign_push(context->tokenv, NULL, TK_WILDCARD);
	return (select_next_tokenizer(context));
}