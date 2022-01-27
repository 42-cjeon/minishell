/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:13:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/27 19:00:13 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"

static char	*prefix_create(const char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(PROJECT_NAME, ": cd: ");
	ret = ft_strjoin(tmp, str);
	free(tmp);
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
