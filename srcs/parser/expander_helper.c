/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:42:08 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:49:25 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expander.h"
#include "libft.h"
#include "tk_types.h"
#include "utils.h"

t_bool exp_is_wildcard_start(t_token_node *curr, t_token_node *next)
{
	if (curr->type == TK_WILDCARD)
		return (TRUE);
	if (curr->type == TK_STRING && next && next->type == TK_WILDCARD)
		return (TRUE);
	return (FALSE);
}

t_bool exp_iswildcard(t_token_node *node)
{
	if (node == NULL)
		return (FALSE);
	return (node->type == TK_STRING || node->type == TK_WILDCARD);
}

t_expander_result	for_each_node(t_tokenv *tokenv, t_expander expander)
{
	t_expander_context	context;
	t_expander_result	result;

	context.tokenv = tokenv;
	context.prev = NULL;
	context.curr = tokenv->head;
	while (context.curr)
	{
		result = expander(&context);
		if (result != EXP_STAY)
			context.prev = context.curr;
		if (result == EXP_CONTINUE)
			context.curr = context.curr->next;
		else if (result == EXP_JUMP)
			context.curr = context.jump_to;
		else if (result == EXP_STAY)
			context.curr = context.curr;
		else
			return (result);
	}
	return (EXP_SUCCESS);
}

size_t	replace_variable(char **str, const size_t start)
{
	size_t	len;
	char	*varname;
	char	*newstr;

	len = 1;
	while ((*str)[len + start] != '\0' \
		&& tk_isidentifier((*str)[len + start]))
		len++;
	if (len == 1)
	{
		if ((*str)[len] == '?')
			return (2); // need implement
		return (1);
	}
	varname = ft_substr(*str, start + 1, len - 1);
	if (varname == NULL)
		return (0);
	newstr = ft_replace_str(*str, start, len, getenv(varname));
	free(varname);
	if (newstr == NULL)
		return (0);
	free(*str);
	*str = newstr;
	return (len);
}