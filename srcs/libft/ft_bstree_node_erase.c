/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree_node_erase.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:23:00 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 11:55:38 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bstnode	*ft_bstnode_find_min(t_bstnode *root)
{
	t_bstnode	*cur;

	cur = root;
	while (cur && cur->left)
	{
		cur = cur->left;
	}
	return (cur);
}

static t_bstnode	*ft_bstnode_erase_do(t_bstnode *bstnode,
						int (*content_compare)(const void *, const void *),
						void (*content_delete)(void *))
{
	t_bstnode	*tmp;

	if (!(bstnode->left))
	{
		tmp = bstnode->right;
		ft_bstnode_delete(bstnode, content_delete);
		return (tmp);
	}
	else if (!(bstnode->right))
	{
		tmp = bstnode->left;
		ft_bstnode_delete(bstnode, content_delete);
		return (tmp);
	}
	tmp = ft_bstnode_find_min(bstnode->right);
	bstnode->content = tmp->content;
	bstnode->right = ft_bstnode_erase(bstnode->right,
			tmp->content, content_compare, content_delete);
	return (bstnode);
}

t_bstnode	*ft_bstnode_erase(t_bstnode *bstnode, void *content,
				int (*content_compare)(const void *, const void *),
				void (*content_delete)(void *))
{
	int	comp;

	if (!bstnode)
		return (NULL);
	comp = content_compare(content, bstnode->content);
	if (comp > 0)
		bstnode->right = ft_bstnode_erase(bstnode->right,
				content, content_compare, content_delete);
	else if (comp < 0)
		bstnode->left = ft_bstnode_erase(bstnode->left,
				content, content_compare, content_delete);
	else
		return (ft_bstnode_erase_do(bstnode,
				content_compare, content_delete));
	return (bstnode);
}
