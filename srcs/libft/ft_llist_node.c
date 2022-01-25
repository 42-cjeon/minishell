/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:04:28 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:38:39 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_llnode	*ft_llnode_create(void *content)
{
	t_llnode	*ret;

	if (content == NULL)
		return (NULL);
	ret = (t_llnode *)ft_malloc(sizeof(t_llnode));
	ret->prev = NULL;
	ret->next = NULL;
	ret->content = content;
	return (ret);
}

void	ft_llnode_delete(t_llnode *node,
			void (*content_delete)(void *))
{
	if (node && content_delete)
	{
		if (node->content)
			content_delete(node->content);
		free(node);
	}
}

void	ft_llnode_print(const t_llnode *node,
			void (*content_print)(const void *c))
{
	if (node && content_print)
		content_print(node->content);
}

void	ft_llnode_trim(t_llnode *node)
{
	t_llnode	*prev;
	t_llnode	*next;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	node->prev = NULL;
	node->next = NULL;
}
