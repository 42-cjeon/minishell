/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:56:19 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:01:30 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSTREE_H
# define BSTREE_H

typedef struct s_bstnode
{
	struct s_bstnode	*left;
	struct s_bstnode	*right;
	void				*content;
}	t_bstnode;

typedef struct s_bstree
{
	t_bstnode	*root;
	void		(*content_delete)(void *);
	int			(*content_compare)(const void *c1, const void *c2);
	void		(*content_print)(void *c);
}	t_bstree;

typedef enum e_torder
{
	TORDER_PRE = 1,
	TORDER_IN,
	TORDER_POST
}	t_torder;

t_bstnode	*ft_bstnode_create(void *content);
void		ft_bstnode_delete(t_bstnode *bstnode,
				void (*content_delete)(void *));
void		ft_bstnode_print(t_bstnode *bstnode,
				void (*content_print)(void *));
t_bstnode	*ft_bstnode_erase(t_bstnode *bstnode, void *content,
				int (*content_compare)(const void *, const void *),
				void (*content_delete)(void *));
void		ft_bstnode_traverse(t_bstnode *bstnode, t_torder torder,
				void (*node_func)(t_bstnode *bstnode, void (*)(void *)),
				void (*content_func)(void *));

t_bstree	*ft_bstree_create(void (*content_delete)(void*),
				int (*content_compare)(const void *c1, const void *c2),
				void (*content_print)(void *c));
void		ft_bstree_delete(t_bstree *bst);
void		ft_bstree_print(const t_bstree *bst);

void		ft_bstree_insert(t_bstree *bst, t_bstnode *node);
void		ft_bstree_erase(t_bstree *bst, void *content);
t_bstnode	**ft_bstree_search(t_bstree *bst, void *content);

#endif
