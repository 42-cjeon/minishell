/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:19 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 16:58:48 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "builtin.h"

int	ft_env(char **cmd, const t_envs *envs)
{
	char	*prefix;

	if (!cmd || !(*cmd) || !envs)
		return (1);
	if (cmd[1])
	{
		errno = ENOENT;
		prefix = ft_strjoin("env: ", cmd[1]);
		if (!prefix)
			ft_perror_texit(PROJECT_NAME, 1);
		ft_perror(prefix);
		return (127);
	}
	envs_print(envs, PORDER_UNSORTED);
	return (0);
}
