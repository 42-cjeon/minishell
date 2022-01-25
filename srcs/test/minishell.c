/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:15:08 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/07 05:22:32 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"
#include "lex.h"
#include "tokenize.h"

int main(int argc, const char *argv[])
{
	int				ret;
	t_tokenv		*tokenv;
	t_token_node	*node;
	static const char *msg[] = {
		"UNESC_STR",
		"QUOTE_STR",
		"DQUOTE_STR",
		"SPACE",
		"SUBSHELL",
		"OPERATOR",
		"WILDCARD",
		"STRING",
		"COMMAND",
		"ARG",
		"HEREDOC",
		"REDIR_INPUT",
		"REDIR_OUTPUT",
		"APPEND",
		"OR",
		"AND",
		"PIPE"
	};
	assert(argc == 2);

	tokenv = malloc(sizeof(t_tokenv));
	if (tokenv == NULL)
	{
		printf("Malloc Fail\n");
		return (-1);
	}
	if ((ret = tokenize(argv[1], tokenv)))
	{
		printf("Tokenize Failed with status : %d\n", ret);
		return (ret);
	}

	if ((ret = expand(tokenv)))
	{
		printf("Expand Failed with status : %d\n", ret);
		return (ret);
	}

	lex(tokenv);

	node = tokenv->head;
	while (node)
	{
		printf("<token>\n\tSTR=[%s]\n", node->token);
		printf("\tTYPE=[%s]\n", msg[node->type]);
		node = node->next;
	}
	tokenv_clear(tokenv);
	free(tokenv);
	return (0);
}