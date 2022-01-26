/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_container.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:04:36 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:46:03 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "expander.h"

void	strv_clear(t_str_node *node)
{
	t_str_node	*next;

	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

t_str_node	*str_node_new(char *str)
{
	t_str_node	*node;

	node = ft_malloc(sizeof(t_str_node));
	node->str = str;
	node->len = ft_strlen(str);
	node->next = NULL;
	return (node);
}

void	str_node_push(t_wildcard_info *wcinfo,
			t_str_node **ptail, t_str_node *node)
{
	if (*ptail == NULL)
	{
		wcinfo->wildcard = node;
		*ptail = node;
	}
	else
	{
		(*ptail)->next = node;
		*ptail = node;
	}
	wcinfo->total_len += node->len;
}

void	wildcard_info_clear(t_wildcard_info *wcinfo)
{
	free(wcinfo->basename);
	free(wcinfo->first_token);
	free(wcinfo->last_token);
	free(wcinfo->nomatch);
	strv_clear(wcinfo->wildcard);
}
