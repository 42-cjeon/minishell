/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 05:24:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/17 16:08:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lex.h"
#include "libft.h"
#include "tokenize.h"
#include "utils.h"

int select_next_lexer(t_token_node *node)
{
	if (node->type == TK_OPERATOR)
	{
		if (streq(node->token, ">"))
			node->type = TK_REDIR_OUTPUT;
		else if (streq(node->token, "<"))
			node->type = TK_REDIR_INPUT;
		else if (streq(node->token, ">>"))
		 	node->type = TK_APPEND;
		else if (streq(node->token, "<<"))
		 	node->type = TK_HEREDOC;
		else if (streq(node->token, "|"))
		 	node->type = TK_PIPE;
		else if (streq(node->token, "||"))
		 	node->type = TK_OR;
		else if (streq(node->token, "&&"))
			node->type = TK_AND;
		else
			return (LEX_EUNKNOWN_OPER);
	}
	return (LEX_SUCCESS);
}

int lex(t_tokenv *tokenv)
{
	t_token_node	*node;
	int result;

	node = tokenv->head;
	while (node)
	{
		result = select_next_lexer(node);
		if (result != LEX_SUCCESS)
			return (result);
		node = node->next;
	}
	return (0);
}