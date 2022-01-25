/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 08:22:16 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdlib.h>

// static char	*stmt_create(const char *str)
// {
// 	char	*ret;
// 	char	*tmp;

// 	tmp = ft_strjoin("export: `", str);
// 	if (!tmp)
// 		ft_perror_texit(PROJECT_NAME, 1);
// 	ret = ft_strjoin(tmp, "\': not a valid identifier");
// 	free(tmp);
// 	return (ret);
// }

static int	is_error(char **str)
{
	int	i;

	i = 0;
	str = NULL;
	// 1. 첫 번째 argument를 체크하여 정상적인 numeric input인지 확인.
		// minishell: exit: aaa: numeric argument required
		// return (255)
		// bash 종료 o
	// 2. argument가 2개 이상 존재하기만 해도 아래 오류 뜸.
		// minishell: exit: too many arguments
		// return (1)
		// bash 종료 x
	// while (str[i])
	// {
		
	// }	
	return (0);
}

int	ft_exit(char **cmd)
{
	int	status;

	if (!cmd || !(*cmd))
		return (1);
	if (is_error(cmd))
	{
		// put error
	}
	if (cmd[1])
	{
		status = ft_atoi(cmd[1]);
		exit(status);
	}
	return (0);
}
