/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:12:21 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 12:11:40 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

static char	*stmt_create(const char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin("unset: `", str);
	if (!tmp)
		ft_perror_texit(PROJECT_NAME, 1);
	ret = ft_strjoin(tmp, "\': not a valid identifier");
	free(tmp);
	return (ret);
}

static int	is_error(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i])
			&& !ft_isdigit(str[i]) && (str[i] != '_'))
			return (1);
		++i;
	}
	return (0);
}

int	ft_unset(char **cmd, const t_envs *envs)
{
	char	*stmt;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (is_error(cmd[i]))
		{
			stmt = stmt_create(cmd[i]);
			ft_perror_custom(PROJECT_NAME, stmt);
			return (1);
		}
		envs_erase(envs, cmd[i]);
		++i;
	}
	return (0);
}
