/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:44:04 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/13 23:32:18 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_with_func(void *content,
					void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*node;

	new_content = f(content);
	if (new_content == NULL)
		return (NULL);
	node = ft_lstnew(new_content);
	if (node == NULL)
	{
		if (del != NULL)
			del(new_content);
		return (NULL);
	}
	return (node);
}

static t_list	*ft_lstappend(t_list **head, t_list *tail, t_list *new)
{
	if (*head == NULL)
		*head = new;
	else
		tail->next = new;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst_head;
	t_list	*new_lst_tail;
	t_list	*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst_head = NULL;
	new_lst_tail = NULL;
	while (lst)
	{
		node = ft_lstnew_with_func(lst->content, f, del);
		if (node == NULL)
		{
			ft_lstclear(&new_lst_head, del);
			return (NULL);
		}
		new_lst_tail = ft_lstappend(&new_lst_head, new_lst_tail, node);
		lst = lst->next;
	}
	return (new_lst_head);
}
