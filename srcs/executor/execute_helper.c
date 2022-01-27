/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:07:01 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:05:40 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"
#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

t_builtin_types	is_builtin(t_command *command)
{
	if (command->type != C_COMMAND)
		return (BUILTIN_NONE);
	if (streq(command->data.c[0], "echo"))
		return (BUILTIN_ECHO);
	if (streq(command->data.c[0], "cd"))
		return (BUILTIN_CD);
	if (streq(command->data.c[0], "pwd"))
		return (BUILTIN_PWD);
	if (streq(command->data.c[0], "export"))
		return (BUILTIN_EXPORT);
	if (streq(command->data.c[0], "unset"))
		return (BUILTIN_UNSET);
	if (streq(command->data.c[0], "env"))
		return (BUILTIN_ENV);
	if (streq(command->data.c[0], "exit"))
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

char	**get_path_arr(t_envs *envs)
{
	char	*path;
	char	**path_arr;

	path = envs_get_value(envs, "PATH");
	if (path == NULL)
		return (NULL);
	path_arr = ft_split(path, ':');
	return (path_arr);
}
