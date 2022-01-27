/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:04 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/27 20:33:35 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	is_nopt;

	i = 1;
	is_nopt = 0;
	if (!cmd || !(*cmd))
		return (1);
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
	{
		is_nopt = 1;
		++i;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (!is_nopt)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
