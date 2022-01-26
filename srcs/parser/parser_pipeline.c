/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:04:16 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:32:02 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tk_types.h"
#include "libft.h"

int	parse_pipeline(t_parser_context *context)
{
	t_pipeline	*pipeline;
	size_t		index;
	int			result;

	pipeline = get_pipeline(context->curr);
	index = 0;
	while (index < pipeline->len)
	{
		result = parse_command(context, &pipeline->commands[index]);
		if (result != P_SUCCESS)
			break ;
		result = parse_pipe(context, index + 1 == pipeline->len);
		if (result != P_SUCCESS)
			break ;
		index++;
	}
	if (result != P_SUCCESS)
		return (clear_pipeline(context));
	push_line_info(context->li, get_cmd_node(C_PIPELINE, pipeline));
	return (next_pipeline(context));
}

int	next_pipeline(t_parser_context *context)
{
	if (context->curr == NULL)
		return (P_SUCCESS);
	if (tk_islogicaloper(context->curr->type))
		return (parse_logical_oper(context));
	return (P_ESYNTEX);
}

int	parse_pipe(t_parser_context *context, int is_last)
{
	if (is_last)
	{
		if (context->curr == NULL)
			return (P_SUCCESS);
		if (context->curr->type == TK_PIPE)
			return (P_ESYNTEX);
		return (P_SUCCESS);
	}
	else
	{
		if (context->curr == NULL)
			return (P_ESYNTEX);
		if (context->curr->type != TK_PIPE)
			return (P_ESYNTEX);
		context->curr = context->curr->next;
		return (P_SUCCESS);
	}
}

t_pipeline	*get_pipeline(t_token_node *node)
{
	size_t		len;
	t_pipeline	*pipeline;

	len = 1;
	while (node)
	{
		if (node->type == TK_PIPE)
			len++;
		node = node->next;
	}
	pipeline = ft_malloc(sizeof(t_pipeline));
	pipeline->childs = ft_calloc(len, sizeof(pid_t));
	pipeline->commands = ft_calloc(len, sizeof(t_command));
	pipeline->len = len;
	return (pipeline);
}
