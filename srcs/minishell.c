/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:32:21 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/28 18:42:26 by cjeon            ###   ########.fr       */
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
#include "utils.h"

void	process_line(char *line, t_shell_info *si)
{
	t_line_info	li;
	int			parse_result;

	ft_memset(&li, 0, sizeof(t_line_info));
	parse_result = parse_line(si, line, &li);
	if (parse_result == P_ESYNTEX)
		si->last_status = 258;
	if (parse_result == P_SUCCESS)
		execute_line(si, li.head);
	line_info_clear(&li);
}

int	main(int argc, char *argv[], const char *envp[])
{
	t_shell_info	si;
	char			*line;
	int				result;

	argc = 0;
	argv = NULL;
	shell_init(&si, envp);
	shell_print_banner();
	while (1)
	{
		line = shell_readline();
		if (!line)
			break ;
		if (streq(line, ""))
		{
			free(line);
			continue ;
		}
		shell_add_history(line);
		process_line(line, &si);
		free(line);
	}
	result = si.last_status;
	shell_deinit(&si);
	return (result);
}
