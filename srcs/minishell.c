/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:32:21 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 13:30:28 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expander.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"
#include "tokenizer.h"
#include "executor.h"
#include "envs.h"

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

void print_li(t_line_info *li)
{
	t_command_node *cnode;

	cnode = li->head;
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
}

void print_tokens(t_tokenv *tokenv)
{
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
	t_token_node *node;
	node = tokenv->head;
	while (node)
	{
		printf("<token>\n\tSTR=[%s]\n", node->token);
		printf("\tTYPE=[%s]\n", msg[node->type]);
		node = node->next;
	}
}

void init_si(t_shell_info *si)
{
	si->default_stdin = ttyname(STDIN_FILENO);
	si->default_stdout = ttyname(STDOUT_FILENO);
	si->default_stderr = ttyname(STDERR_FILENO);
	si->last_status = 0;
}

int process_line(char *line)
{
	t_tokenv	tokenv;
	t_line_info	li;
	t_shell_info si;

	tokenv_init(&tokenv);
	if (tokenize(line, &tokenv) || expand(&tokenv) || lex(&tokenv))
	{
		tokenv_clear(&tokenv);
		si.last_status = 1;
		return (1);
	}
	ft_memset(&li, 0, sizeof(t_line_info));
	//print_tokens(&tokenv);
	if (parse(&tokenv, &li))
	{
		printf("Parse FAIL\n");
		tokenv_clear(&tokenv);
		si.last_status = 1;
		return (1);
	}
	init_si(&si);
	
	//print_li(&li);
	execute_line(&si, li.head);
	tokenv_clear(&tokenv);
	line_info_clear(&li);
	return (0);
}

int main(int argc, char *argv[], const char *envp[])
{
	char	*line;
	t_envs	*envs;

	argc = 0;
	argv = NULL;
	envs = envs_create(envp);
	shell_init();
	shell_print_banner();
	while (1)
	{
		line = shell_readline();
		shell_add_history(line);
		process_line(line);
		free(line);
	}
	envs_delete(envs);
	return (0);
}
