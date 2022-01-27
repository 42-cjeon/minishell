/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:20:18 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:06:46 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft.h"
#include "parser.h"

void	pipes_init(t_pipes *pipes)
{
	pipes->prev_pipe[0] = -1;
	pipes->prev_pipe[1] = -1;
	pipes->curr_pipe[0] = -1;
	pipes->curr_pipe[1] = -1;
}

void	close_pipes(t_pipes *pipes)
{
	if (pipes->curr_pipe[0] != -1)
		ft_close(pipes->curr_pipe[0]);
	if (pipes->curr_pipe[1] != -1)
		ft_close(pipes->curr_pipe[1]);
	if (pipes->prev_pipe[0] != -1)
		ft_close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		ft_close(pipes->prev_pipe[1]);
}

void	move_next_pipe(t_pipes *pipes, int islast)
{
	if (pipes->prev_pipe[0] != -1)
		ft_close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		ft_close(pipes->prev_pipe[1]);
	pipes->prev_pipe[0] = pipes->curr_pipe[0];
	pipes->prev_pipe[1] = pipes->curr_pipe[1];
	if (!islast)
		ft_pipe(pipes->curr_pipe);
	else
	{
		pipes->curr_pipe[0] = -1;
		pipes->curr_pipe[1] = -1;
	}
}
