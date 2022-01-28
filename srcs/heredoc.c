/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:19:06 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/28 18:49:14 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "heredoc.h"
#include "libft.h"
#include "readline/readline.h"

void	heredoc_fmake(const char *pname, const char *lim)
{
	char	*line;
	int		fd;

	if (!pname || !lim)
		return ;
	fd = open(pname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_perror_texit(PROJECT_NAME, 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (!ft_strcmp(line, lim))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

void	heredoc_fremove(const char *pname)
{
	if (!pname)
		return ;
	if (unlink(pname) < 0)
		ft_perror_texit(PROJECT_NAME, 1);
}
