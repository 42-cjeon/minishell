/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:34:08 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 03:56:41 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "parser.h"

typedef struct s_shell_info
{
	const char *default_stdin;
	const char *default_stdout;
	const char *default_stderr;
	int last_status;
}	t_shell_info;

typedef enum e_builtin_types
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin_types;

typedef struct s_pipes
{
	int prev_pipe[2];
	int curr_pipe[2];
}	t_pipes;

void execute_line(t_shell_info *si, t_command_node *node);

#endif