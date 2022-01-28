/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:06:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 15:59:18 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

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

t_bool	is_excutable(const char *fullpath)
{
	struct stat	file_stat;

	if (stat(fullpath, &file_stat))
		return (FALSE);
	return ((file_stat.st_mode & S_IFMT) == S_IFREG);
}

int	search_execve(char **path, char **cmd, char **envs)
{
	size_t	i;
	char	*cmd_temp;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		if (*path[i] == '/')
		{
			cmd_temp = ft_strjoin("/", cmd[0]);
			cmd_path = ft_strjoin(path[i], cmd_temp);
			if (is_excutable(cmd_path))
			{
				if (execve(cmd_path, cmd, envs))
					ft_perror_texit(PROJECT_NAME, 1);
			}
			free(cmd_path);
			free(cmd_temp);
		}
		i++;
	}
	return (1);
}

void	execute_simple_cmd(t_shell_info *si, char **cmd)
{
	char	**envs_arr;
	char	**path_arr;

	envs_arr = envs_to_arr(si->envs);
	if (ft_strchr(cmd[0], '/'))
	{
		if (!is_excutable(cmd[0]))
			ft_perror_texit(PROJECT_NAME, 1);
		if (execve(cmd[0], cmd, envs_to_arr(si->envs)))
			ft_perror_texit(PROJECT_NAME, 1);
	}
	path_arr = get_path_arr(si->envs);
	if (!streq(cmd[0], "") && path_arr)
		search_execve(path_arr, cmd, envs_arr);
	envs_arr_delete(envs_arr);
	envs_arr_delete(path_arr);
	ft_putstr_fd(PROJECT_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
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
		return (ft_exit(cmd));
	else
		return (1);
}
