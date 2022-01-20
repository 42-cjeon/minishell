/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 05:24:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:49:33 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenizer.h"
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
		{
			ft_perror_custom("minishell: unknown operator", node->token);
			return (1);
		}
	}
	return (0);
}

int lex(t_tokenv *tokenv)
{
	t_token_node	*node;

	node = tokenv->head;
	while (node)
	{
		if (select_next_lexer(node))
			return (1);
		node = node->next;
	}
	return (0);
}