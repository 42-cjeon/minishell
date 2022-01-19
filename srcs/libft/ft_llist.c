/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:05:05 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/19 14:11:47 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_llist	*ft_llist_create(void (*content_delete)(void**),
			int (*content_issame)(const void *c1, const void *c2),
			void (*content_print)(const void *c))
{
	t_llist	*ret;

	ret = (t_llist *)ft_malloc(sizeof(t_llist));
	ret->content_delete = content_delete;
	ret->content_issame = content_issame;
	ret->content_print = content_print;
	ret->first = NULL;
	ret->last = NULL;
	ret->size = 0;
	return (ret);
}

void	ft_llist_delete(t_llist **lst)
{
	t_llnode	*cur;
	t_llnode	*next;

	if ((lst == NULL) || ((*lst) == NULL))
		return ;
	cur = (*lst)->first;
	while (cur != NULL)
	{
		next = cur->next;
		ft_llnode_delete(&cur, (*lst)->content_delete);
		cur = next;
	}
	free(*lst);
	(*lst) = NULL;
}

void	ft_llist_print(const t_llist *lst)
{
	t_llnode	*cur;

	if (lst == NULL)
		return ;
	cur = lst->first;
	while (cur != NULL)
	{
		ft_llnode_print(cur, lst->content_print);
		cur = cur->next;
	}
}
