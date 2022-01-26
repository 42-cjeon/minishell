/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:50:37 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:41:53 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expander.h"
#include "libft.h"
#include "utils.h"

void	add_first_token(t_wildcard_info *wcinfo, const char *path)
{
	size_t	path_len;
	size_t	last_slash;

	if (path == NULL)
	{
		wcinfo->basename = ft_strdup("");
		wcinfo->first_token = ft_strdup("");
		wcinfo->nomatch = ft_strdup("*");
	}
	else if (!find_last_slash(path, &last_slash, &path_len))
	{
		wcinfo->basename = ft_strdup("");
		wcinfo->first_token = ft_strdup(path);
		wcinfo->nomatch = ft_strdup(path);
	}
	else
	{
		wcinfo->basename = ft_substr(path, 0, last_slash + 1);
		wcinfo->first_token = ft_substr(path, last_slash + 1, \
											path_len - last_slash);
		wcinfo->nomatch = ft_strdup(path);
	}
}

void	wildcard_push_last(t_wildcard_info *wcinfo,
			t_str_node **tail, t_str_node **last)
{
	if (*last)
		str_node_push(wcinfo, tail, *last);
	*last = NULL;
}

void	move_next_token_node(t_expander_context *context)
{
	context->prev->next = context->curr->next;
	free(context->curr);
	context->curr = context->prev->next;
}

void	append_nomatch_str(t_wildcard_info *wcinfo, char *token)
{
	char	*new_str;

	new_str = ft_strjoin(wcinfo->nomatch, token);
	free(wcinfo->nomatch);
	wcinfo->nomatch = new_str;
}

void	append_last_token(t_wildcard_info *wcinfo, t_str_node *last)
{
	if (last)
		wcinfo->last_token = last->str;
	else
		wcinfo->last_token = ft_strdup("");
	free(last);
}
