/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_container.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 21:10:49 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/02 04:10:33 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenize.h"

void	tokenv_push(t_tokenv *tokenv, t_token_node *new)
{
	if (tokenv->tail == NULL)
	{
		tokenv->head = new;
		tokenv->tail = new;
	}
	else
	{
		tokenv->tail->next = new;
		tokenv->tail = new;
	}
}

int		tokenv_assign_push(t_tokenv *tokenv, char *token, t_token_type type)
{
	t_token_node	*node;

	node = token_node_new(token, type);
	if (node == NULL)
	{
		free(token);
		return (1);
	}
	tokenv_push(tokenv, node);
	return (0);
}

t_token_node *token_node_new(char *token, t_token_type type)
{
	t_token_node *node;

	node = malloc(sizeof(t_token_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->token = token;
	node->next = NULL;
	return (node);
}

void	tokenv_init(t_tokenv *tokenv)
{
	tokenv->head = NULL;
	tokenv->tail = NULL;
}

void	tokenv_clear(t_tokenv *tokenv)
{
	t_token_node *curr;
	t_token_node *next;

	curr = tokenv->head;
	while (curr)
	{
		next = curr->next;
		free(curr->token);
		free(curr);
		curr = next;
	}
}