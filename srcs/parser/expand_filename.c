/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:26:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 09:34:07 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expander.h"
#include "tokenizer.h"
#include "libft.h"

void	get_wildcard_strs(t_expander_context *context, t_wildcard_info *wcinfo)
{
	t_str_node	*tail;
	t_str_node	*last;

	tail = NULL;
	last = NULL;
	while (exp_iswildcard(context->curr))
	{
		wildcard_push_last(wcinfo, &tail, &last);
		if (context->curr->type == TK_STRING)
		{
			last = str_node_new(context->curr->token);
			append_nomatch_str(wcinfo, context->curr->token);
		}
		else
			append_nomatch_str(wcinfo, "*");
		move_next_token_node(context);
	}
	append_last_token(wcinfo, last);
}

void	get_wildcard_info(t_expander_context *context, t_wildcard_info *wcinfo)
{
	add_first_token(wcinfo, context->curr->token);
	context->prev->next = context->curr->next;
	free(context->curr->token);
	free(context->curr);
	context->curr = context->prev->next;
	get_wildcard_strs(context, wcinfo);
}

int	expand_filename(t_expander_context *context)
{
	t_tokenv		matched;
	t_wildcard_info	wcinfo;

	if (!exp_is_wildcard_start(context->curr, context->curr->next))
		return (EXP_CONTINUE);
	ft_memset(&wcinfo, 0, sizeof(t_wildcard_info));
	get_wildcard_info(context, &wcinfo);
	ft_memset(&matched, 0, sizeof(t_tokenv));
	if (append_matched(&wcinfo, &matched) == EXP_NOMATCH)
		append_nomatch(&wcinfo, &matched);
	context->prev->next = matched.head;
	matched.tail->next = context->curr;
	return (EXP_STAY);
}