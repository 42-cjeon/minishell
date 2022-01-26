/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 09:57:52 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:29:46 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

void	push_line_info(t_line_info *li, t_command_node *node)
{
	if (li->head == NULL)
	{
		li->head = node;
		li->tail = node;
	}
	else
	{
		li->tail->next = node;
		li->tail = node;
	}
}

int	clear_pipeline(t_parser_context *context)
{
	(void)context;
	return (P_ESYNTEX);
}

void	push_redir(t_redir **head, t_redir *new)
{
	t_redir	*curr;

	curr = *head;
	if (curr == NULL)
		*head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	clear_redir(t_redir **head)
{
	t_redir	*curr;
	t_redir	*next;

	curr = *head;
	while (curr)
	{
		next = curr->next;
		free(curr->target);
		free(curr);
		curr = curr->next;
	}
	*head = NULL;
}
