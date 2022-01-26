/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:13:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 13:09:49 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>

static char	*prefix_create(const char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(PROJECT_NAME, ": cd: ");
	if (!tmp)
		ft_perror_texit(PROJECT_NAME, 1);
	ret = ft_strjoin(tmp, str);
	if (!ret)
		ft_perror_texit(PROJECT_NAME, 1);
	return (ret);
}

int	ft_cd(char **cmd)
{
	char	*prefix;

	if (!cmd || !(*cmd))
		return (1);
	if (cmd[1])
	{
		if (chdir(cmd[1]) == -1)
		{
			prefix = prefix_create(cmd[1]);
			ft_perror(prefix);
			free(prefix);
			return (1);
		}
	}
	return (0);
}
