/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logical_oper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:04:14 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 16:24:56 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "tk_types.h"

int	next_logical_oper(t_parser_context *context)
{
	t_token_type	type;

	if (context->curr == NULL)
		return (P_EUNEXPECTED_ENDL);
	type = context->curr->type;
	if (type == TK_SUBSHELL || type == TK_STRING \
		|| tk_isredir(type))
		return (parse_pipeline(context));
	return (P_ESYNTEX);
}

int	parse_logical_oper(t_parser_context *context)
{
	t_command_node	*node;

	if (context->curr->type == TK_AND)
		node = get_cmd_node(C_AND, NULL);
	else
		node = get_cmd_node(C_OR, NULL);
	context->curr = context->curr->next;
	push_line_info(context->li, node);
	return (next_logical_oper(context));
}
