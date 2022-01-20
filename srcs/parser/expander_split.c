/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:31:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 09:31:10 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "tk_types.h"
#include "tokenizer.h"
#include "libft.h"

int	handle_string(char *token, t_tokenv *tokenv)
{
	size_t			len;
	char			*subtoken;
	t_token_node	*node;

	len = 0;
	while (!tk_isnul(token[len]) && !tk_isspace(token[len]))
		len++;
	subtoken = ft_substr(token, 0, len);
	node = token_node_new(subtoken, TK_UNESCAPED_STRING);
	tokenv_push(tokenv, node);
	if (token[len] == '\0')
		return (EXP_SUCCESS);
	return (handle_space(token + len, tokenv));
}

int	handle_space(char *token, t_tokenv *tokenv)
{
	t_token_node *node;

	while (tk_isspace(*token))
		token++;
	node = token_node_new(NULL, TK_SPACE);
	tokenv_push(tokenv, node);
	if (*token == '\0')
		return (EXP_SUCCESS);
	return (handle_string(token, tokenv));
}

int	handle_empty(char *token, t_tokenv *tokenv)
{
	char			*newtoken;
	t_token_node	*node;

	newtoken = ft_strdup(token);
	node = token_node_new(newtoken, TK_UNESCAPED_STRING);
	tokenv_push(tokenv, node);
	return (EXP_SUCCESS);
}

t_tokenv *split_token(char *token)
{
	t_tokenv			*tokenv;
	t_expander_result	result;
	
	tokenv = ft_malloc(sizeof(t_tokenv));
	tokenv_init(tokenv);
	if (*token == '\0')
		result = handle_empty(token, tokenv);
	else if (tk_isspace(*token))
		handle_space(token, tokenv);
	else
		handle_string(token, tokenv);
	return (tokenv);
}