/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:20:32 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:25:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "executor.h"
#include "libft.h"
#include "shell.h"

void	replace_fd(const char *filename, int to_replace_fd, int oflag)
{
	int fd;

	fd = open(filename, oflag);
	if (fd == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	ft_dup2(fd, to_replace_fd);
	ft_close(fd);
}

void	restore_default_fd(t_shell_info *si)
{
	replace_fd(si->default_stdin, STDIN_FILENO, O_RDONLY);
	replace_fd(si->default_stdout, STDOUT_FILENO, O_WRONLY);
	replace_fd(si->default_stderr, STDERR_FILENO, O_WRONLY);
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
