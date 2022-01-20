/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:31:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:35:12 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk_types.h"
#include "tokenizer.h"
#include "libft.h"

int	select_next_tokenizer(t_tokenizer_context *context)
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

int	tokenize(const char *raw_line, t_tokenv *tokenv)
{
	t_tokenizer_context	context;
	int					result;

	tokenv_init(tokenv);
	context.tokenv = tokenv;
	context.raw_line = raw_line;
	context.cursor = 0;
	result = select_next_tokenizer(&context);
	if (result == TKZR_EUNEXPECTEDNL)
		ft_perror_custom("minishell", "unclosed sequence detected");
	return (result);
}
