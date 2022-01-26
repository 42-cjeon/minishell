/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_container.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 21:10:49 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:36:55 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenizer.h"

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

void	tokenv_assign_push(t_tokenv *tokenv, char *token, t_token_type type)
{
	t_token_node	*node;

	node = token_node_new(token, type);
	tokenv_push(tokenv, node);
}

t_token_node	*token_node_new(char *token, t_token_type type)
{
	t_token_node	*node;

	node = ft_malloc(sizeof(t_token_node));
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
	t_token_node	*curr;
	t_token_node	*next;

	curr = tokenv->head;
	while (curr)
	{
		next = curr->next;
		free(curr->token);
		free(curr);
		curr = next;
	}
}
