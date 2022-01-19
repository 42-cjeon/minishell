/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:32:21 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/19 14:12:50 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "expand.h"
#include "lex.h"
#include "tokenize.h"
#include "shell.h"
#include "libft.h"

int main(int argc, char *argv[], char *envp[])
{
	int				ret;
	t_tokenv		*tokenv;
	t_token_node	*node;
	char			*line;
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
	argc = 0;
	argv = NULL;
	envp = NULL;
	shell_init();
	shell_print_banner();
	while (1)
	{
		line = shell_readline();
		shell_add_history(line);
		/* to do something */
		tokenv = ft_malloc(sizeof(t_tokenv));
		if ((ret = tokenize(line, tokenv)))
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
		free(line);
	}
	return (0);
}
