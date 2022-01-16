/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:15:08 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/16 19:10:02 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"
#include "lex.h"
#include "parser.h"
#include "tokenize.h"

void print_redir(t_command *cmd)
{
	t_redir *redir;
	const char *redirtype[] = {
		"",
		"IN",
		"HEREDOC",
		"OUT",
		"APPEND"
	};

	redir = cmd->redir;
	while (redir)
	{
		printf("    <redir-%s> :%s:\n",redirtype[redir->type], redir->target);
		redir = redir->next;
	}
}

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
	
	if ((ret = lex(tokenv)))
	{
		printf("Lexical analize FAIL\n");
		return (ret);
	}

	node = tokenv->head;
	while (node)
	{
		printf("<token>\n\tSTR=:%s:\n", node->token);
		printf("\tTYPE=[%s]\n", msg[node->type]);
		node = node->next;
	}
	t_line_info li;
	li.head = NULL;
	li.tail = NULL;

	t_command_node *cnode;
	
	if ((ret = parse(tokenv, &li)))
	{
		printf("Syntex Error\n");
		return (ret);
	}

	cnode = li.head;
	while (cnode)
	{
		if (cnode->type == C_AND)
			printf("<AND />\n");
		else if (cnode->type == C_OR)
			printf("<OR />\n");
		else
		{
			printf("<PIPELINE>\n");
			for (size_t i = 0; i < cnode->pipeline->len; i++)
			{
				char **data;

				if (cnode->pipeline->commands[i].type == C_COMMAND)
				{
					data = (cnode->pipeline->commands[i].data.c);
					printf("  <cmd>\n    :");
					for (int i = 0; data[i]; i++)
						printf(data[i + 1] ? "%s " : "%s", data[i]);
					printf(":\n");
					print_redir(&cnode->pipeline->commands[i]);
					printf("  </cmd>\n");
				}
				else if (cnode->pipeline->commands[i].type == C_SUBSHELL)
				{
					printf("  <subshell>\n");
					printf("    :%s:\n", cnode->pipeline->commands[i].data.s);
					printf("  </subshell>\n");
				}
			}
			printf("</PIPELINE>\n");
		}
		cnode = cnode->next;
	}

	return (0);
}