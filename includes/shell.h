/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:13 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 12:34:42 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "envs.h"

typedef struct s_shell_info
{
	const char	*default_stdin;
	const char	*default_stdout;
	const char	*default_stderr;
	int			last_status;
	t_envs		*envs;
}	t_shell_info;

void	shell_init(t_shell_info *si, const char *envp[]);
void	shell_deinit(t_shell_info *si);
void	shell_print_banner(void);
char	*shell_readline(void);
void	shell_add_history(const char *str);

#endif
