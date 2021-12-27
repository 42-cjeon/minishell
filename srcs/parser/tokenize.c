/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:31:22 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/27 04:23:28 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenize.h"
#include "tk_types.h"

t_tokenizer_result	select_next_tokenizer(t_tokenizer_context *context)
{
	if (context_peek_cmp(context, tk_isnul))
		return (TKZR_SUCCESS);
	else if (context_peek_cmp(context, tk_issubshellend))
		return (TKZR_EUNEXPECTEDNL);
	else if (context_peek_cmp(context, tk_isquote))
		return (tokenize_quote(context));
	else if (context_peek_cmp(context, tk_isdquote))
		return (tokenize_dquote(context));
	else if (context_peek_cmp(context, tk_isspace))
		return (tokenize_space(context));
	else if (context_peek_cmp(context, tk_issubshellstart))
		return (tokenize_subshell(context));
	else if (context_peek_cmp(context, tk_isoperator))
		return (tokenize_operator(context));
	else if (context_peek_cmp(context, tk_iswildcard))
		return (tokenize_wildcard(context));
	else
		return (tokenize_unescaped(context));
}

t_tokenizer_result	tokenize_unescaped(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = context->cursor++;
	len = seek_first_eq(context, tk_isspacialchar) + 1;
	token = ft_substr(context->raw_line, start, len);
	if (token == NULL)
		return (TKZR_EMALLOC);
	if (tokenv_assign_push(context->tokenv, token, TK_UNESCAPED_STRING))
		return (TKZR_EMALLOC);	
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_quote(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = ++context->cursor;
	len = seek_first_eq(context, tk_isquote);
	if (context_peek_cmp(context, tk_isnul))
		return (TKZR_EUNEXPECTEDNL);
	context->cursor++;
	token = ft_substr(context->raw_line, start, len);
	if (token == NULL)
		return (TKZR_EMALLOC);
	if (tokenv_assign_push(context->tokenv, token, TK_QUOTED_STRING))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_dquote(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = ++context->cursor;
	len = seek_first_eq(context, tk_isdquote);
	if (context_peek_cmp(context, tk_isnul))
		return (TKZR_EUNEXPECTEDNL);
	context->cursor++;
	token = ft_substr(context->raw_line, start, len);
	if (token == NULL)
		return (TKZR_EMALLOC);
	if (tokenv_assign_push(context->tokenv, token, TK_DQUOTED_STRING))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_space(t_tokenizer_context *context)
{
	seek_first_nq(context, tk_isspace);
	if (tokenv_assign_push(context->tokenv, NULL, TK_SPACE))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_subshell(t_tokenizer_context *context)
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
	if (token == NULL)
		return (TKZR_EMALLOC);
	if (tokenv_assign_push(context->tokenv, token, TK_SUBSHELL))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_operator(t_tokenizer_context *context)
{
	size_t			len;
	size_t			start;
	char			*token;

	start = context->cursor;
	len = seek_first_nq_op(context);
	token = ft_substr(context->raw_line, start, len);
	if (token == NULL)
		return (TKZR_EMALLOC);
	if (tokenv_assign_push(context->tokenv, token, TK_OPERATOR))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize_wildcard(t_tokenizer_context *context)
{
	context->cursor++;
	if (tokenv_assign_push(context->tokenv, NULL, TK_WILDCARD))
		return (TKZR_EMALLOC);
	return (select_next_tokenizer(context));
}

t_tokenizer_result	tokenize(const char *raw_line, t_tokenv *tokenv)
{
	t_tokenizer_context context;

	tokenv_init(tokenv);
	context.tokenv = tokenv;
	context.raw_line = raw_line;
	context.cursor = 0;
	return (select_next_tokenizer(&context));
}