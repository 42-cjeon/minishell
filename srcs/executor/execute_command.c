/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:06:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 18:48:47 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "builtin.h"
#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"
#include "utils.h"

int	execute_subshell(t_shell_info *si, char *cmd)
{
	t_line_info	li;
	int			parse_result;

	ft_memset(&li, 0, sizeof(t_line_info));
	parse_result = parse_line(si, cmd, &li);
	if (parse_result == P_ESYNTEX)
		si->last_status = 258;
	if (parse_result == P_SUCCESS)
		execute_line(si, li.head);
	line_info_clear(&li);
	exit(si->last_status);
}

int	search_execve(char **path, char **cmd, char **envs)
{
	size_t	i;
	char	*cmd_temp;
	char	*cmd_path;
	int		ftype;

	i = 0;
	while (path[i])
	{
		if (*path[i] == '/')
		{
			cmd_temp = ft_strjoin("/", cmd[0]);
			cmd_path = ft_strjoin(path[i], cmd_temp);
			free(cmd_temp);
			ftype = check_ftype(cmd_path);
			if (ftype == FT_DIR)
				command_perror_texit(cmd[0], "is a directory", 126);
			else if (ftype == FT_FILE && execve(cmd_path, cmd, envs))
				command_perror_texit(cmd[0], strerror(errno), 126);
		}
		i++;
	}
	return (1);
}

void	execute_simple_cmd(t_shell_info *si, char **cmd)
{
	char	**envs_arr;
	char	**path_arr;
	int		ftype;

	envs_arr = envs_to_arr(si->envs);
	if (ft_strchr(cmd[0], '/'))
	{
		ftype = check_ftype(cmd[0]);
		if (ftype == FT_NOTFOUND)
			command_perror_texit(cmd[0], strerror(errno), 127);
		else if (ftype == FT_DIR)
			command_perror_texit(cmd[0], "is a directory", 126);
		else if (execve(cmd[0], cmd, envs_to_arr(si->envs)))
			command_perror_texit(cmd[0], strerror(errno), 127);
	}
	path_arr = get_path_arr(si->envs);
	if (!streq(cmd[0], "") && path_arr)
		search_execve(path_arr, cmd, envs_arr);
	envs_arr_delete(envs_arr);
	envs_arr_delete(path_arr);
	command_perror_texit(cmd[0], "command not found", 127);
}

int	execute_builtin(t_shell_info *si, char **cmd, t_builtin_types type)
{
	if (type == BUILTIN_ECHO)
		return (ft_echo(cmd));
	else if (type == BUILTIN_CD)
		return (ft_cd(cmd));
	else if (type == BUILTIN_PWD)
		return (ft_pwd(cmd));
	else if (type == BUILTIN_EXPORT)
		return (ft_export(cmd, si->envs));
	else if (type == BUILTIN_UNSET)
		return (ft_unset(cmd, si->envs));
	else if (type == BUILTIN_ENV)
		return (ft_env(cmd, si->envs));
	else if (type == BUILTIN_EXIT)
		return (ft_exit(cmd, si->last_status));
	else
		return (1);
}
