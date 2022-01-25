/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:19 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 07:37:58 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "errno.h"

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
		ft_perror_texit(prefix, 127);
	}
	else
		envs_print(envs, PORDER_UNSORTED);
	return (0);
}
