/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:13:54 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:38:13 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_bstree	*ft_bstree_create(void (*content_delete)(void*),
				int (*content_compare)(const void *c1, const void *c2),
				void (*content_print)(void *c))
{
	t_bstree	*ret;

	ret = (t_bstree *)ft_malloc(sizeof(t_bstree));
	ret->root = NULL;
	ret->content_delete = content_delete;
	ret->content_compare = content_compare;
	ret->content_print = content_print;
	return (ret);
}

void	ft_bstree_delete(t_bstree *bst)
{
	if (bst)
	{
		ft_bstnode_traverse(bst->root, TORDER_POST,
			(void (*)(t_bstnode *, void (*)(void *)))ft_bstnode_delete,
			(void (*)(void *))bst->content_delete);
		free(bst);
	}	
}

void	ft_bstree_print(const t_bstree *bst)
{
	if (bst)
	{
		ft_bstnode_traverse(bst->root, TORDER_IN,
			(void (*)(t_bstnode *, void (*)(void *)))ft_bstnode_print,
			(void (*)(void *))bst->content_print);
	}
}

t_bstnode	**ft_bstree_search(t_bstree *bst, void *content)
{
	t_bstnode	**cur;
	int			comp;

	cur = &(bst->root);
	while ((*cur) != NULL)
	{
		comp = bst->content_compare(content, (*cur)->content);
		if (comp > 0)
			cur = &((*cur)->right);
		else if (comp < 0)
			cur = &((*cur)->left);
		else
			break ;
	}
	return (cur);
}
