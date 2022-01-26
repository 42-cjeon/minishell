/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 07:49:25 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:38:46 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tk_types.h"
#include "tokenizer.h"

int	tokenize_quote(t_tokenizer_context *context)
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
	tokenv_assign_push(context->tokenv, token, TK_QUOTED_STRING);
	return (select_next_tokenizer(context));
}

int	tokenize_dquote(t_tokenizer_context *context)
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
	tokenv_assign_push(context->tokenv, token, TK_DQUOTED_STRING);
	return (select_next_tokenizer(context));
}
