/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:07:01 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 17:29:24 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>

#include "envs.h"
#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

int	is_builtin(t_command *command)
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

void	command_perror_texit(char *cmd, char *msg, int status)
{
	ft_putstr_fd(PROJECT_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(status);
}

int	check_ftype(char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat))
		return (FT_NOTFOUND);
	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
		return (FT_DIR);
	return (FT_FILE);
}
