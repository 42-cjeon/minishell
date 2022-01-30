/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:18:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/30 13:50:44 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "executor.h"
#include "libft.h"

int	wait_childs(t_pipeline *pipeline)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < pipeline->len)
	{
		if (pipeline->childs[i] == 0)
			status = (1U << 8);
		else if (waitpid(pipeline->childs[i], &status, 0) == -1)
			ft_perror_texit(PROJECT_NAME, 1);
		i++;
	}
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	else if (ft_wifsignaled(status))
		return (ft_wtermsig(status));
	else
		return (status % 128);
}

int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	else if (ft_wifsignaled(status))
		return (ft_wtermsig(status));
	else
		return (status % 128);
}
