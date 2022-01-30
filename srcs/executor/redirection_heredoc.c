/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:07:03 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/30 11:31:50 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "executor.h"
#include "fcntl.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"
#include "utils.h"

static int	redirect_lines(t_shell_info *si, int heredoc_pipe[], \
							const t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = shell_readline(si, "> ");
		if (line == NULL)
		{
			ft_close(heredoc_pipe[0]);
			ft_close(heredoc_pipe[1]);
			return (1);
		}
		if (streq(line, redir->target))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, heredoc_pipe[1]);
		free(line);
	}
	return (0);
}

int	handle_redir_heredoc(t_shell_info *si, const t_redir *redir)
{
	int		heredoc_pipe[2];
	int		stdout_backup;
	int		result;

	replace_fd(si->default_stdin, STDIN_FILENO);
	stdout_backup = ft_dup(STDOUT_FILENO);
	replace_fd(si->default_stdout, STDOUT_FILENO);
	ft_pipe(heredoc_pipe);
	result = redirect_lines(si, heredoc_pipe, redir);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	ft_close(stdout_backup);
	ft_dup2(heredoc_pipe[0], STDIN_FILENO);
	ft_close(heredoc_pipe[1]);
	ft_close(heredoc_pipe[0]);
	return (result);
}
