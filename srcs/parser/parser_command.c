/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:06:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/29 21:26:41 by cjeon            ###   ########.fr       */
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

static t_bool	tk_iscommand(t_token_node *node)
{
	if (node == NULL)
		return (FALSE);
	return (
		node->type == TK_STRING \
		|| node->type == TK_SUBSHELL \
		|| tk_isredir(node->type)
	);
}

int	validate_command(t_token_node *curr, t_command *cmd)
{
	size_t	cmd_len;

	if (!tk_iscommand(curr))
		return (P_ESYNTEX);
	cmd_len = 0;
	while (tk_iscommand(curr))
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
