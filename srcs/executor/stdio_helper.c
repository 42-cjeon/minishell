/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:20:32 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:11:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "executor.h"
#include "libft.h"
#include "shell.h"

void	restore_default_fd(t_shell_info *si)
{
	int	fd[3];

	fd[STDIN_FILENO] = open(si->default_stdin, O_RDONLY);
	if (fd[STDIN_FILENO] == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	fd[STDOUT_FILENO] = open(si->default_stdout, O_WRONLY);
	if (fd[STDOUT_FILENO] == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	fd[STDERR_FILENO] = open(si->default_stderr, O_WRONLY);
	if (fd[STDERR_FILENO] == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	ft_dup2(fd[STDIN_FILENO], STDIN_FILENO);
	ft_dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	ft_dup2(fd[STDERR_FILENO], STDERR_FILENO);
	ft_close(fd[STDIN_FILENO]);
	ft_close(fd[STDOUT_FILENO]);
	ft_close(fd[STDERR_FILENO]);
}

void	replace_stdio_fd(t_shell_info *si, t_pipes *pipes)
{
	int	fd;

	if (pipes->prev_pipe[0] == -1)
	{
		fd = open(si->default_stdin, O_RDONLY);
		if (fd == -1)
			ft_perror_texit(PROJECT_NAME, 1);
		ft_dup2(fd, STDIN_FILENO);
		ft_close(fd);
	}
	else
		ft_dup2(pipes->prev_pipe[0], STDIN_FILENO);
	if (pipes->curr_pipe[0] == -1)
	{
		fd = open(si->default_stdout, O_WRONLY);
		if (fd == -1)
			ft_perror_texit(PROJECT_NAME, 1);
		ft_dup2(fd, STDOUT_FILENO);
		ft_close(fd);
	}
	else
		ft_dup2(pipes->curr_pipe[1], STDOUT_FILENO);
}
