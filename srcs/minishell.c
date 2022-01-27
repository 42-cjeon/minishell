/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:32:21 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/27 14:58:17 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "executor.h"
#include "expander.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"
#include "tokenizer.h"

void process_line(char *line, t_shell_info *si)
{
	t_line_info li;

	li.head = parse_line(si, line);
	if (li.head == NULL)
		si->last_status = 258;
	execute_line(si, li.head);
	line_info_clear(&li);
}

int main(int argc, char *argv[], const char *envp[])
{
	t_shell_info	si;
	char			*line;

	argc = 0;
	argv = NULL;
	shell_init(&si, envp);
	shell_print_banner();
	while (1)
	{
		line = shell_readline();
		if (!line)
			break ;
		shell_add_history(line);
		process_line(line, &si);
		free(line);
	}
	shell_deinit(&si);
	return (0);
}
