/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:08:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/27 04:17:20 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "expand.h"
#include "tokenize.h"
#include "exp_types.h"
#include "tk_types.h"

t_expander_result	expand_filename(t_expander_context *context)
{
	(void)context;
	return (EXP_SUCCESS);
}

#include <stdio.h>
void print_tk(t_tokenv *v)
{
	t_token_node *node;

	node = v->head;
	while (node)
	{
		printf("TK=[%s]\n", node->token);
		node = node->next;
	}
}

t_expander_result	expand_word_splitting(t_expander_context *context)
{
	t_tokenv *splited_tokenv;
	t_token_node *curr;
	t_token_node *prev;

	curr = *context->curr;
	prev = *context->prev;
	if (curr->type != TK_UNESCAPED_STRING)
		return (EXP_SUCCESS);
	splited_tokenv = split_token(curr->token);
	if (splited_tokenv == NULL)
		return (EXP_EMALLOC);
	if (prev == NULL)
		context->tokenv->head = splited_tokenv->head;
	else
		prev->next = splited_tokenv->head;
	splited_tokenv->tail->next = curr->next;
	free(curr->token);
	free(curr);
	*context->prev = NULL;
	*context->curr = splited_tokenv->tail;
	free(splited_tokenv);
	return (EXP_SUCCESS);
}

t_expander_result	expand_variable(t_expander_context *context)
{
	t_token_node	*curr;
	size_t			cursor;
	size_t			len;

	curr = *context->curr;
	if (curr->type != TK_DQUOTED_STRING && curr->type != TK_UNESCAPED_STRING)
		return (EXP_SUCCESS);
	cursor = 0;
	while (curr->token[cursor] != '\0')
	{
		if (exp_isdollarsign(curr->token[cursor]))
		{
			len = replace_variable(&curr->token, cursor);
			if (len == 0)
				return (EXP_EMALLOC);
			cursor += len;
		}
		else
			cursor++;
	}
	return (EXP_SUCCESS);
}

t_bool	tk_isstringtype(const t_token_type type)
{
	return (type == TK_QUOTED_STRING \
			|| type == TK_DQUOTED_STRING \
			|| type == TK_UNESCAPED_STRING);
}

t_expander_result	merge_string_tokens(t_expander_context *context)
{
	t_token_node	*curr;
	t_token_node	*next;
	char			*merged_token;

	curr = *context->curr;
	next = curr->next;
	if (next == NULL || !tk_isstringtype(curr->type) || !tk_isstringtype(next->type))
		return (EXP_SUCCESS);
	merged_token = ft_strjoin(curr->token, next->token);
	if (merged_token == NULL)
		return (EXP_EMALLOC);
	free(curr->token);
	free(next->token);
	curr->next = next->next;
	free(next);
	curr->token = merged_token;
	curr->type = TK_STRING;
	return (EXP_SUCCESS);
}

t_expander_result	for_each_node(t_tokenv *tokenv, t_expander expander)
{
	t_token_node		*prev;
	t_token_node		*curr;
	t_expander_result	result;

	prev = NULL;
	curr = tokenv->head;
	while (curr)
	{
		result = expander(&(t_expander_context){tokenv, &prev, &curr});
		if (result != EXP_SUCCESS)
			return (result);
		prev = curr;
		curr = curr->next;
	}
	return (EXP_SUCCESS);
}

t_expander_result	expand(t_tokenv *tokenv)
{
	t_expander_result	result;

	result = for_each_node(tokenv, expand_variable);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(tokenv, expand_word_splitting);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(tokenv, merge_string_tokens);
	if (result != EXP_SUCCESS)
		return (result);
	return (for_each_node(tokenv, expand_filename));
}
