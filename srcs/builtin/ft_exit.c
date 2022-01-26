/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:49:42 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 10:31:59 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*nonnumeric_stmt_create(const char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin("exit: ", str);
	if (!tmp)
		ft_perror_texit(PROJECT_NAME, 1);
	ret = ft_strjoin(tmp, ": numeric argument required");
	free(tmp);
	return (ret);
}

static int	is_nonnumeric_error(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '+'
		|| str[0] != '-' || !ft_isdigit(str[0]))
		return (1);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

static int	is_argnum_error(char **str)
{
	int	argc;

	argc = 0;
	while (str[argc])
		++argc;
	if (argc > 2)
		return (1);
	return (0);
}

int	ft_exit(char **cmd)
{
	int		status;
	char	*stmt;

	if (!cmd || !(*cmd))
		return (1);
	if (is_nonnumeric_error(cmd[1]))
	{
		stmt = nonnumeric_stmt_create(cmd[1]);
		// 이 에러는 bash가 종료됨.
		ft_perror_custom_texit(PROJECT_NAME, stmt, 1);
	}
	else if (is_argnum_error(cmd))
	{
		ft_perror_custom(PROJECT_NAME, "exit: too many arguments");
		// 이 에러는 bash가 종료되지 않음.
		return (1);
	}
	if (cmd[1])
	{
		status = ft_atoi(cmd[1]);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(status);
	}
	return (0);
}
