/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:07:06 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:11:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"

int	handle_redir_in(const t_redir *redir)
{
	int	target_fd;

	target_fd = open(redir->target, O_RDONLY);
	if (target_fd == -1)
	{
		ft_perror(PROJECT_NAME);
		return (1);
	}
	ft_dup2(target_fd, STDIN_FILENO);
	ft_close(target_fd);
	return (0);
}

int	handle_redir_out(const t_redir *redir)
{
	int	target_fd;

	target_fd = open(redir->target, O_WRONLY | O_CREAT, 0644);
	if (target_fd == -1)
	{
		ft_perror(PROJECT_NAME);
		return (1);
	}
	ft_dup2(target_fd, STDOUT_FILENO);
	ft_close(target_fd);
	return (0);
}

int	handle_redir_append(const t_redir *redir)
{
	int	target_fd;

	target_fd = open(redir->target, O_WRONLY | O_APPEND, 0644);
	if (target_fd == -1)
	{
		ft_perror(PROJECT_NAME);
		return (1);
	}
	ft_dup2(target_fd, STDOUT_FILENO);
	ft_close(target_fd);
	return (0);
}

int	handle_redirect(t_shell_info *si, t_redir *redir)
{
	int	is_redir_fail;

	is_redir_fail = 0;
	while (redir && !is_redir_fail)
	{
		if (redir->type == REDIR_IN)
			is_redir_fail = handle_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			is_redir_fail = handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			is_redir_fail = handle_redir_append(redir);
		else if (redir->type == REDIR_HEREDOC)
			is_redir_fail = handle_redir_heredoc(si, redir);
		redir = redir->next;
	}
	return (is_redir_fail);
}