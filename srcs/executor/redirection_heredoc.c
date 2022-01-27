/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:07:03 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:35:28 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "executor.h"
#include "fcntl.h"
#include "libft.h"
#include "parser.h"
#include "readline/readline.h"
#include "shell.h"
#include "utils.h"

int	handle_redir_heredoc(t_shell_info *si, const t_redir *redir)
{
	char	*line;
	int		heredoc_pipe[2];

	replace_fd(si->default_stdin, STDIN_FILENO, O_RDONLY);
	ft_pipe(heredoc_pipe);
	while (1)
	{
		line = readline("> ");
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
	ft_close(heredoc_pipe[1]);
	ft_dup2(heredoc_pipe[0], STDIN_FILENO);
	return (0);
}
