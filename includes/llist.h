/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:03:41 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/19 16:50:01 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H

typedef struct s_llnode
{
	struct s_llnode	*prev;
	struct s_llnode	*next;
	void			*content;
}	t_llnode;

typedef struct s_llist
{
	t_llnode	*first;
	t_llnode	*last;
	int			size;
	void		(*content_delete)(void*);
	int			(*content_compare)(const void *c1, const void *c2);
	void		(*content_print)(const void *c);
}	t_llist;

t_llnode		*ft_llnode_create(void *content);
void			ft_llnode_delete(t_llnode *node,
					void (*content_delete)(void *));
void			ft_llnode_print(const t_llnode *node,
					void (*content_print)(const void *c));
void			ft_llnode_trim(t_llnode *node);

t_llist			*ft_llist_create(void (*content_delete)(void*),
					int (*content_compare)(const void *c1, const void *c2),
					void (*content_print)(const void *c));
void			ft_llist_delete(t_llist *lst);
void			ft_llist_print(const t_llist *lst);

void			ft_llist_push_front(t_llist *lst, t_llnode *node);
void			ft_llist_push_back(t_llist *lst, t_llnode *node);
t_llnode		*ft_llist_pop(t_llist *lst, void *content);
t_llnode		*ft_llist_pop_front(t_llist *lst);
t_llnode		*ft_llist_pop_back(t_llist *lst);
t_llnode		*ft_llist_search(t_llist *lst, const void *content);

#endif
