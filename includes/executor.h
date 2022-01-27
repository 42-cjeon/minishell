/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:34:08 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 13:54:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "shell.h"

typedef enum e_builtin_types
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin_types;

typedef struct s_pipes
{
	int	prev_pipe[2];
	int	curr_pipe[2];
}	t_pipes;

void	execute_line(t_shell_info *si, t_command_node *node);
int handle_redir_in(const t_redir *redir);
int handle_redir_out(const t_redir *redir);
int handle_redir_append(const t_redir *redir);
int	handle_redir_heredoc(t_shell_info *si, const t_redir *redir);
int handle_redirect(t_shell_info *si, t_redir *redir);
void restore_default_fd(t_shell_info *si);
t_builtin_types is_builtin(t_command *command);
int execute_builtin(t_shell_info *si, char **cmd, t_builtin_types type);
int execute_subshell(t_shell_info *si, char *cmd);
char **get_path_arr(t_envs *envs);
void search_execve(char **path, char **cmd, char **envs);
void execute_simple_cmd(t_shell_info *si, char **cmd);
void close_pipes(t_pipes *pipes);
void fork_execute_command(t_shell_info *si, t_pipes *pipes, t_command *command, pid_t *child);
void pipes_init(t_pipes *pipes);
void move_next_pipe(t_pipes *pipes, int islast);
void replace_stdio_fd(t_shell_info *si, t_pipes *pipes);
int wait_childs(t_pipeline *pipeline);
int wait_child(pid_t pid);
int execute_pipeline(t_shell_info *si, t_pipeline *pipeline);
int execute_single_cmd(t_shell_info *si, t_pipeline *pipeline);
void execute_line(t_shell_info *si, t_command_node *node);

#endif