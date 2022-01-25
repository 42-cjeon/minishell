/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree_node_traverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:27 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 11:55:01 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_bstnode_traverse_pre(t_bstnode *bstnode,
				void (*node_func)(t_bstnode *, void (*)(void *)),
				void (*content_func)(void *))
{
	if (bstnode && node_func && content_func)
	{
		node_func(bstnode, content_func);
		ft_bstnode_traverse_pre(bstnode->left, node_func, content_func);
		ft_bstnode_traverse_pre(bstnode->right, node_func, content_func);
	}
}

static void	ft_bstnode_traverse_in(t_bstnode *bstnode,
				void (*node_func)(t_bstnode *, void (*)(void *)),
				void (*content_func)(void *))
{
	if (bstnode && node_func && content_func)
	{
		ft_bstnode_traverse_in(bstnode->left, node_func, content_func);
		node_func(bstnode, content_func);
		ft_bstnode_traverse_in(bstnode->right, node_func, content_func);
	}
}

static void	ft_bstnode_traverse_post(t_bstnode *bstnode,
				void (*node_func)(t_bstnode *, void (*)(void *)),
				void (*content_func)(void *))
{
	if (bstnode && node_func && content_func)
	{
		ft_bstnode_traverse_post(bstnode->left, node_func, content_func);
		ft_bstnode_traverse_post(bstnode->right, node_func, content_func);
		node_func(bstnode, content_func);
	}
}

void	ft_bstnode_traverse(t_bstnode *bstnode, t_torder torder,
			void (*node_func)(t_bstnode *, void (*)(void *)),
			void (*content_func)(void *))
{
	if (torder == TORDER_PRE)
		ft_bstnode_traverse_pre(bstnode, node_func, content_func);
	else if (torder == TORDER_IN)
		ft_bstnode_traverse_in(bstnode, node_func, content_func);
	else if (torder == TORDER_POST)
		ft_bstnode_traverse_post(bstnode, node_func, content_func);
}
