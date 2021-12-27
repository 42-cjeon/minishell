/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:31:22 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 17:32:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "expand.h"
#include "tk_types.h"
#include "tokenize.h"

t_expander_result	handle_string(char *token, t_tokenv *tokenv)
{
	size_t len;
	char	*subtoken;
	t_token_node *node;

	len = 0;
	while (!tk_isnul(token[len]) && !tk_isspace(token[len]))
		len++;
	subtoken = ft_substr(token, 0, len);
	if (subtoken == NULL)
		return (EXP_EMALLOC);
	node = token_node_new(subtoken, TK_UNESCAPED_STRING);
	if (node == NULL)
	{
		free(subtoken);
		return (EXP_EMALLOC);
	}
	tokenv_push(tokenv, node);
	if (token[len] == '\0')
		return (EXP_SUCCESS);
	return (handle_space(token + len, tokenv));
}

t_expander_result	handle_space(char *token, t_tokenv *tokenv)
{
	t_token_node *node;

	while (tk_isspace(*token))
		token++;
	node = token_node_new(NULL, TK_SPACE);
	if (node == NULL)
		return (EXP_EMALLOC);
	tokenv_push(tokenv, node);
	if (*token == '\0')
		return (EXP_SUCCESS);
	return (handle_string(token, tokenv));
}

t_expander_result	handle_empty(char *token, t_tokenv *tokenv)
{
	char			*newtoken;
	t_token_node	*node;

	newtoken = ft_strdup(token);
	if (newtoken == NULL)
		return (EXP_EMALLOC);
	node = token_node_new(newtoken, TK_UNESCAPED_STRING);
	if (node == NULL)
	{
		free(newtoken);
		return (EXP_EMALLOC);
	}
	tokenv_push(tokenv, node);
	return (EXP_SUCCESS);
}

t_tokenv *split_token(char *token)
{
	t_tokenv			*tokenv;
	t_expander_result	result;
	tokenv = malloc(sizeof(tokenv));
	if (tokenv == NULL)
		return (NULL);
	tokenv_init(tokenv);
	if (*token == '\0')
		result = handle_empty(token, tokenv);
	else if (tk_isspace(*token))
		result = handle_space(token, tokenv);
	else
		result = handle_string(token, tokenv);
	if (result != EXP_SUCCESS)
	{
		tokenv_clear(tokenv);
		free(tokenv);
		return (NULL);
	}
	return (tokenv);
}