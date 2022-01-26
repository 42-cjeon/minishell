/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:03 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 17:59:08 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "envs.h"
#include "libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "shell.h"

static void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	shell_init(t_shell_info *si, const char *envp[])
{
	si->default_stdin = ttyname(STDIN_FILENO);
	si->default_stdout = ttyname(STDOUT_FILENO);
	si->default_stderr = ttyname(STDERR_FILENO);
	si->last_status = 0;
	si->envs = envs_create(envp);
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	signal(SIGALRM, handler);
	signal(SIGTSTP, handler);
	signal(SIGTTIN, handler);
	signal(SIGTTOU, handler);
}

void	shell_deinit(t_shell_info *si)
{
	if (si->envs)
		envs_delete(si->envs);
	ft_memset(si, 0, sizeof(t_shell_info));
}

char	*shell_readline(void)
{
	char	*ret;

	ret = readline("minishell$ ");
	return (ret);
}

void	shell_add_history(const char *str)
{
	if (str && ft_isprint(str[0]))
		add_history(str);
}
