/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:03 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/30 12:27:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

#include "envs.h"
#include "libft.h"
#include "shell.h"

void	shell_init(t_shell_info *si, const char *envp[])
{
	si->default_stdin = ft_dup(STDIN_FILENO);
	si->default_stdout = ft_dup(STDOUT_FILENO);
	si->default_stderr = ft_dup(STDERR_FILENO);
	si->isterminal = isatty(STDOUT_FILENO) \
					&& isatty(STDIN_FILENO) \
					&& isatty(STDERR_FILENO);
	if (si->isterminal)
	{
		tcgetattr(STDOUT_FILENO, &si->default_term_attr);
		si->readline_term_attr = si->default_term_attr;
		si->readline_term_attr.c_lflag &= (~ECHOCTL);
	}
	si->last_status = 0;
	si->envs = envs_create(envp);
}

void	shell_deinit(t_shell_info *si)
{
	if (si->envs)
		envs_delete(si->envs);
	ft_close(si->default_stdin);
	ft_close(si->default_stdout);
	ft_close(si->default_stderr);
}
