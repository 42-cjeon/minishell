/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:59 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 08:22:34 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "envs.h"
#include <stdlib.h>

static char	*stmt_create(const char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin("export: `", str);
	if (!tmp)
		ft_perror_texit(PROJECT_NAME, 1);
	ret = ft_strjoin(tmp, "\': not a valid identifier");
	free(tmp);
	return (ret);
}

static int	is_error(char *str)
{
	int		ret;
	t_cenv	*cenv;
	int		i;

	ret = 0;
	i = 0;
	cenv = cenv_create(str);
	if (ft_isdigit(cenv->key[0]))
		ret = 1;
	else
	{
		while (cenv->key[i])
		{
			if (!ft_isalpha(cenv->key[i]) && !ft_isdigit(cenv->key[i])
				&& (cenv->key[i] != '_') && (cenv->key[i] != '-'))
			{
				ret = 1;
				break ;
			}
			++i;
		}	
	}
	cenv_delete(cenv);
	return (ret);
}

int	ft_export(char **cmd, const t_envs *envs)
{
	char	*stmt;
	int		i;

	i = 1;
	if (cmd[i])
		envs_print(envs, PORDER_SORTED);
	else
	{
		while (cmd[i])
		{
			if (is_error(cmd[i]))
			{
				stmt = stmt_create(cmd[i]);
				ft_perror_custom_texit(PROJECT_NAME, stmt, 1);
			}
			envs_insert(envs, cmd[i]);
			++i;
		}	
	}
	return (0);
}
