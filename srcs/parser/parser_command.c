/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:06:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 15:21:15 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"

int	parse_command(t_parser_context *context, t_command *cmd)
{
	size_t	i;

	if (context->curr == NULL \
		|| validate_command(context->curr, cmd) != P_SUCCESS)
		return (P_ESYNTEX);
	i = 0;
	while (context->curr && (context->curr->type == TK_SUBSHELL \
		|| context->curr->type == TK_STRING \
		|| tk_isredir(context->curr->type)))
	{
		if (tk_isredir(context->curr->type))
			context->curr = context->curr->next;
		else if (cmd->type == C_COMMAND)
			move_string(&cmd->data.c[i++], &context->curr->token);
		else if (cmd->type == C_SUBSHELL)
			move_string(&cmd->data.s, &context->curr->token);
		context->curr = context->curr->next;
	}
	return (P_SUCCESS);
}

int	validate_command(t_token_node *curr, t_command *cmd)
{
	size_t	cmd_len;

	cmd_len = 0;
	while (curr && (curr->type == TK_SUBSHELL || curr->type == TK_STRING \
		|| tk_isredir(curr->type)))
	{
		if (check_cmd_type(cmd, curr->type) != P_SUCCESS)
			return (P_ESYNTEX);
		if (tk_isredir(curr->type))
		{
			if (parse_redir(curr, cmd))
				return (P_ESYNTEX);
			curr = curr->next;
		}
		else
			cmd_len++;
		curr = curr->next;
	}
	if (cmd->type == C_COMMAND)
	{
		cmd->data.c = ft_calloc(cmd_len + 1, sizeof(char *));
		cmd->data.c[cmd_len] = NULL;
	}
	return (P_SUCCESS);
}

t_command_node	*get_cmd_node(t_command_node_type type, t_pipeline *pipeline)
{
	t_command_node	*node;

	node = ft_malloc(sizeof(t_command_node));
	node->type = type;
	node->pipeline = pipeline;
	node->next = NULL;
	return (node);
}
