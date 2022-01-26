/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:05:05 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 17:08:56 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

t_llist	*ft_llist_create(void (*content_delete)(void*),
			int (*content_compare)(const void *c1, const void *c2),
			void (*content_print)(const void *c))
{
	t_llist	*ret;

	ret = (t_llist *)ft_malloc(sizeof(t_llist));
	ret->content_delete = content_delete;
	ret->content_compare = content_compare;
	ret->content_print = content_print;
	ret->first = NULL;
	ret->last = NULL;
	ret->size = 0;
	return (ret);
}

void	ft_llist_delete(t_llist *lst)
{
	t_llnode	*cur;
	t_llnode	*next;

	if (lst == NULL)
		return ;
	cur = lst->first;
	while (cur != NULL)
	{
		next = cur->next;
		ft_llnode_delete(cur, lst->content_delete);
		cur = next;
	}
	free(lst);
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

t_llnode	*ft_llist_search(t_llist *lst, void *content)
{
	t_llnode	*cur;

	if (!lst || !content)
		return (NULL);
	cur = lst->first;
	while (cur != NULL)
	{
		if (!(lst->content_compare(cur->content, content)))
			break ;
		cur = cur->next;
	}
	return (cur);
}
