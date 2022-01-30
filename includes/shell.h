/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:13 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/30 09:32:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <termios.h>

# include "envs.h"

typedef struct s_shell_info
{
	int				default_stdin;
	int				default_stdout;
	int				default_stderr;
	int				isterminal;
	struct termios	default_term_attr;
	struct termios	readline_term_attr;
	int				last_status;
	t_envs			*envs;
}	t_shell_info;

void	shell_init(t_shell_info *si, const char *envp[]);
void	shell_deinit(t_shell_info *si);
void	shell_print_banner(void);
char	*shell_readline(t_shell_info *si, char *prompt);
void	shell_add_history(const char *str);

#endif
