/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 09:57:52 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 15:58:10 by cjeon            ###   ########.fr       */
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
