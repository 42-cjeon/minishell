/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:28:03 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:35:28 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llnode	*ft_llist_pop_front(t_llist *lst)
{
	t_llnode	*first;

	if (!lst)
		return (NULL);
	first = lst->first;
	if (first)
	{
		if (lst->size == 1)
			lst->last = NULL;
		lst->first = first->next;
		ft_llnode_trim(first);
		--(lst->size);
	}
	return (first);
}

t_llnode	*ft_llist_pop_back(t_llist *lst)
{
	t_llnode	*last;

	if (!lst)
		return (NULL);
	last = lst->last;
	if (last)
	{
		if (lst->size == 1)
			lst->first = NULL;
		lst->last = last->prev;
		ft_llnode_trim(last);
		--(lst->size);
	}
	return (last);
}

t_llnode	*ft_llist_pop(t_llist *lst, void *content)
{
	t_llnode	*node;

	if (!lst || !content)
		return (NULL);
	node = ft_llist_search(lst, content);
	if (node)
	{
		if (node == lst->first)
			lst->first = lst->first->next;
		if (node == lst->last)
			lst->last = lst->last->prev;
		ft_llnode_trim(node);
		--(lst->size);
	}
	return (node);
}
