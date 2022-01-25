/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:52:45 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:36:40 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bstree_insert(t_bstree *bst, t_bstnode *node)
{
	t_bstnode	**pos;

	pos = ft_bstree_search(bst, node->content);
	if (*pos)
	{
		node->left = (*pos)->left;
		node->right = (*pos)->right;
		ft_bstnode_delete((*pos), bst->content_delete);
		(*pos) = node;
	}
	else
		(*pos) = node;
}

void	ft_bstree_erase(t_bstree *bst, void *content)
{
	if (!bst || !content)
		return ;
	bst->root = ft_bstnode_erase(bst->root,
			content, bst->content_compare, bst->content_delete);
}
