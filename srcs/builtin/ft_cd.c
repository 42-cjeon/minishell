/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:13:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 07:38:18 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>

int	ft_cd(char **cmd)
{
	if (!cmd || !(*cmd))
		return (1);
	if (cmd[1])
	{
		if (chdir(cmd[1]) == -1)
			ft_perror_texit(PROJECT_NAME, 1);
	}
	return (0);
}
