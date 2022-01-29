/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:04 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/30 00:01:58 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin.h"

static int	is_arg_nopt(char *cmd)
{
	int	is_nopt;
	int	i;

	is_nopt = 0;
	i = 1;
	if (cmd[0] != '-')
		return (0);
	while (cmd[i] == 'n')
	{
		is_nopt = 1;
		++i;
	}
	if (cmd[i] != '\0')
		is_nopt = 0;
	return (is_nopt);
}

static int	is_nopt_set(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && is_arg_nopt(cmd[i]))
		++i;
	return (i);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	is_nopt;

	i = 1;
	is_nopt = 0;
	if (!cmd || !(*cmd))
		return (1);
	is_nopt = is_nopt_set(&(cmd[1]));
	i += is_nopt;
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
