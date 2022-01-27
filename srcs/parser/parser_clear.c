/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:48:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 15:51:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

void	pipeline_clear(t_pipeline *pipeline)
{
	free(pipeline->childs);
	command_clear(pipeline->commands, pipeline->len);
	free(pipeline);
}

void	command_node_clear(t_command_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == C_PIPELINE)
		pipeline_clear(node->pipeline);
	free(node);
}

void	line_info_clear(t_line_info *li)
{
	t_command_node	*curr;
	t_command_node	*next;

	curr = li->head;
	while (curr)
	{
		next = curr->next;
		command_node_clear(curr);
		curr = next;
	}
}
