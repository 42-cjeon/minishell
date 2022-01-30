/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:20:32 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/30 09:14:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "executor.h"
#include "libft.h"
#include "shell.h"

void	replace_fd(int fd, int to_replace_fd)
{
	ft_dup2(fd, to_replace_fd);
}

void	restore_default_fd(t_shell_info *si)
{
	replace_fd(si->default_stdin, STDIN_FILENO);
	replace_fd(si->default_stdout, STDOUT_FILENO);
	replace_fd(si->default_stderr, STDERR_FILENO);
}

void	replace_stdio_fd(t_shell_info *si, t_pipes *pipes)
{
	if (pipes->prev_pipe[0] == -1)
		replace_fd(si->default_stdin, STDIN_FILENO);
	else
		ft_dup2(pipes->prev_pipe[0], STDIN_FILENO);
	if (pipes->curr_pipe[0] == -1)
		replace_fd(si->default_stdout, STDOUT_FILENO);
	else
		ft_dup2(pipes->curr_pipe[1], STDOUT_FILENO);
}
