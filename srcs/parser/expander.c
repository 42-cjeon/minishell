/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/5 00:08:39 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/02 20:00:31 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tk_types.h"
#include "expander.h"

int	expand_word_splitting(t_expander_context *context)
{
	t_tokenv	*splited_tokenv;

	if (context->curr->type != TK_UNESCAPED_STRING)
		return (EXP_CONTINUE);
	splited_tokenv = split_token(context->curr->token);
	if (context->prev == NULL)
		context->tokenv->head = splited_tokenv->head;
	else
		context->prev->next = splited_tokenv->head;
	splited_tokenv->tail->next = context->curr->next;
	context->jump_to = context->curr->next;
	free(context->curr->token);
	free(context->curr);
	free(splited_tokenv);
	return (EXP_JUMP);
}

int	expand_variable(t_expander_context *context)
{
	size_t	cursor;
	size_t	len;

	if (context->curr->type != TK_DQUOTED_STRING \
		&& context->curr->type != TK_UNESCAPED_STRING)
		return (EXP_CONTINUE);
	cursor = 0;
	while (context->curr->token[cursor] != '\0')
	{
		if (tk_isdollarsign(context->curr->token[cursor]))
		{
			len = replace_variable(context->si, &context->curr->token, cursor);
			cursor += len;
		}
		else
			cursor++;
	}
	return (EXP_CONTINUE);
}

int	merge_string_tokens(t_expander_context *context)
{
	char			*merged_token;
	t_token_node	*next;

	next = context->curr->next;
	if (tk_isstringtype(context->curr->type))
		context->curr->type = TK_STRING;
	if (context->curr->type != TK_STRING \
		|| next == NULL || !tk_isstringtype(next->type))
		return (EXP_CONTINUE);
	merged_token = ft_strjoin(context->curr->token, next->token);
	if (merged_token == NULL)
		return (EXP_EMALLOC);
	free(context->curr->token);
	free(next->token);
	context->curr->next = next->next;
	free(next);
	context->curr->token = merged_token;
	return (EXP_STAY);
}

int	del_space_node(t_expander_context *context)
{
	if (context->curr->type != TK_SPACE)
		return (EXP_CONTINUE);
	context->jump_to = context->curr->next;
	if (context->prev == NULL)
		context->tokenv->head = context->jump_to;
	else
		context->prev->next = context->jump_to;
	free(context->curr);
	return (EXP_JUMP);
}

int	expand(t_shell_info *si, t_tokenv *tokenv)
{
	t_expander_result	result;

	result = for_each_node(si, tokenv, expand_variable);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(si, tokenv, expand_word_splitting);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(si, tokenv, merge_string_tokens);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(si, tokenv, expand_filename);
	if (result != EXP_SUCCESS)
		return (result);
	for_each_node(si, tokenv, del_space_node);
	return (EXP_SUCCESS);
}
