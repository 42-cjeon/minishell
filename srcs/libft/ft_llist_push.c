/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:05:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/19 14:11:41 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_llist_push_front(t_llist *lst, t_llnode *node)
{
	t_llnode	*prev_first;

	if ((lst == NULL) || (node == NULL))
		return ;
	prev_first = lst->first;
	lst->first = node;
	if (prev_first)
	{
		prev_first->prev = node;
		node->next = prev_first;
	}
	else
	{
		lst->last = node;
	}
	++(lst->size);
}

void	ft_llist_push_back(t_llist *lst, t_llnode *node)
{
	t_llnode	*prev_last;

	if ((lst == NULL) || (node == NULL))
		return ;
	prev_last = lst->last;
	lst->last = node;
	if (prev_last)
	{
		prev_last->next = node;
		node->prev = prev_last;
	}
	else
	{
		lst->first = node;
	}
	++(lst->size);
}
