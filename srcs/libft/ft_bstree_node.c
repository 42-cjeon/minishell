/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstree_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:13:59 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:38:25 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_bstnode	*ft_bstnode_create(void *content)
{
	t_bstnode	*ret;

	ret = ft_malloc(sizeof(t_bstnode));
	ret->left = NULL;
	ret->right = NULL;
	ret->content = content;
	return (ret);
}

void	ft_bstnode_delete(t_bstnode *bstnode,
			void (*content_delete)(void *))
{
	if (bstnode && content_delete)
	{
		if (bstnode->content)
			content_delete(bstnode->content);
		free(bstnode);
	}
}

void	ft_bstnode_print(t_bstnode *bstnode,
			void (*content_print)(void *))
{
	if (bstnode && bstnode->content && content_print)
		content_print(bstnode->content);
}
