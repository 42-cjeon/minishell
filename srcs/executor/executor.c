/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:01:41 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/25 10:46:36 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

int handle_redir_in(const t_redir *redir)
{
	int	target_fd;
	
	target_fd = open(redir->target, O_RDONLY);
	if (target_fd == -1)
	{
		ft_perror("minishell");
		return (1);
	}
	ft_dup2(target_fd, STDIN_FILENO);
	ft_close(target_fd);
	return (0);
}

int handle_redir_out(const t_redir *redir)
{
	int target_fd;

	target_fd = open(redir->target, O_WRONLY | O_CREAT, 0644);
	if (target_fd == -1)
	{
		ft_perror("minishell");
		return (1);
	}
	ft_dup2(target_fd, STDOUT_FILENO);
	ft_close(target_fd);
	return (0);
}

int handle_redir_append(const t_redir *redir)
{
	int	target_fd;

	target_fd = open(redir->target, O_WRONLY | O_APPEND, 0644);
	if (target_fd == -1)
	{
		ft_perror("minishell");
		return (1);
	}
	ft_dup2(target_fd, STDOUT_FILENO);
	ft_close(target_fd);
	return (0);
}

int handle_redir_heredoc(const t_redir *redir)
{
	(void)redir;
	return (1);
}

int handle_redirect(t_redir *redir)
{
	int is_redir_fail;

	is_redir_fail = 0;
	while (redir && !is_redir_fail)
	{
		if (redir->type == REDIR_IN)
			is_redir_fail = handle_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			is_redir_fail = handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			is_redir_fail = handle_redir_append(redir);
		else if (redir->type == REDIR_HEREDOC)
			is_redir_fail = handle_redir_heredoc(redir);
		redir = redir->next;
	}
	return (is_redir_fail);
}

void restore_default_fd(t_shell_info *si)
{
	int fd[3];

	fd[STDIN_FILENO] = open(si->default_stdin, O_RDONLY);
	if (fd == -1)	
		ft_perror_texit(PROJECT_NAME, 1);
	fd[STDOUT_FILENO] = open(si->default_stdout, O_WRONLY);
	if (fd == -1)	
		ft_perror_texit(PROJECT_NAME, 1);
	fd[STDERR_FILENO] = open(si->default_stderr, O_WRONLY);
	if (fd == -1)	
		ft_perror_texit(PROJECT_NAME, 1);
	ft_dup2(fd[STDIN_FILENO], STDIN_FILENO);
	ft_dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	ft_dup2(fd[STDERR_FILENO], STDERR_FILENO);
	ft_close(fd[STDIN_FILENO]);
	ft_close(fd[STDOUT_FILENO]);
	ft_close(fd[STDERR_FILENO]);
}

t_builtin_types is_builtin(t_command *command)
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

int execute_builtin(char **cmd, t_builtin_types type)
{
	(void)cmd;
	(void)type;
	/*
	if (type == BUILTIN_ECHO)
	if (type == BUILTIN_CD)
	if (type == BUILTIN_PWD)
	if (type == BUILTIN_EXPORT)
	if (type == BUILTIN_UNSET)
	if (type == BUILTIN_ENV)
	if (type == BUILTIN_EXIT)
	*/
	return (0);
}

int execute_subshell(char *cmd)
{
	(void)cmd;
	return (999);
	/* call parser */
}

int execute_simple_cmd(char **cmd)
{
	return (execve(cmd[0], cmd, NULL));
}

void close_pipes(t_pipes *pipes)
{
	if (pipes->curr_pipe[0] != -1)
		ft_close(pipes->curr_pipe[0]);
	if (pipes->curr_pipe[1] != -1)
		ft_close(pipes->curr_pipe[1]);
	if (pipes->prev_pipe[0] != -1)
		ft_close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		ft_close(pipes->prev_pipe[1]);
}

void fork_execute_command(t_pipes *pipes, t_command *command, pid_t *child)
{
	t_builtin_types	type;
	pid_t			pid;
	
	pid = fork();
	if (pid == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	else if (pid == 0)
	{
		if (handle_redirect(command->redir))
			exit(1);
		close_pipes(pipes);
		type = is_builtin(command);
		if (type)
			exit(execute_builtin(command->data.c, type)); 
		else if (command->type == C_SUBSHELL)
			exit(execute_subshell(command->data.s));
		else /* type == C_COMMAND */
			exit(execute_simple_cmd(command->data.c));
	}
	else if (pid > 0)
		*child = pid;
}

void pipes_init(t_pipes *pipes)
{
	pipes->prev_pipe[0] = -1;
	pipes->prev_pipe[1] = -1;
	pipes->curr_pipe[0] = -1;
	pipes->curr_pipe[1] = -1;
}

void move_next_pipe(t_pipes *pipes, int islast)
{
	if (pipes->prev_pipe[0] != -1)
		ft_close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		ft_close(pipes->prev_pipe[1]);
	pipes->prev_pipe[0] = pipes->curr_pipe[0];
	pipes->prev_pipe[1] = pipes->curr_pipe[1];
	if (!islast)
		ft_pipe(pipes->curr_pipe);
	else
	{
		pipes->curr_pipe[0] = -1;
		pipes->curr_pipe[1] = -1;
	}
}

void replace_stdio_fd(t_shell_info *si, t_pipes *pipes)
{
	int fd;

	if (pipes->prev_pipe[0] == -1)
	{
		fd = open(si->default_stdin, O_WRONLY);
		if (fd == -1)
			ft_perror_texit(PROJECT_NAME, 1);
		ft_dup2(fd, STDIN_FILENO);
		ft_close(fd);
	}
	else
		ft_dup2(pipes->prev_pipe[0], STDIN_FILENO);
	if (pipes->curr_pipe[0] == -1)
	{
		fd = open(si->default_stdout, O_RDONLY);
		if (fd == -1)
			ft_perror_texit(PROJECT_NAME, 1);
		ft_dup2(fd, STDOUT_FILENO);
		ft_close(fd);
	}
	else 
		ft_dup2(pipes->curr_pipe[1], STDOUT_FILENO);
}

int ft_wifexited(int status)
{
	return ((status & 0177) == 0);
}

int ft_wifsignaled(int status)
{
	return ((status & 0177) != 0);
}

int ft_wexitstatus(int status)
{
	return (((status >> 8) & 0x000000ff) % 128);
}

int ft_wtermsig(int status)
{
	return ((status & 0177) + 128);
}

int wait_childs(t_pipeline *pipeline)
{
	size_t i;
	int status;

	i = 0;
	while (i < pipeline->len)
	{
		if (waitpid(pipeline->childs[i], &status, 0))
			ft_perror_texit(PROJECT_NAME, 1);
		i++;
	}
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	else if (ft_wifsignaled(status))
		return (ft_wtermsig(status));
	else
		return (status % 128);
}

int wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	else if (ft_wifsignaled(status))
		return (ft_wtermsig(status));
	else
		return (status % 128);
}

int execute_pipeline(t_shell_info *si, t_pipeline *pipeline)
{
	t_pipes	pipes;
	size_t	i;

	pipes_init(&pipes);
	move_next_pipe(&pipes, FALSE);
	replace_stdio_fd(si, &pipes);
	fork_execute_command(&pipes, &pipeline->commands[0], &pipeline->childs[0]);
	i = 1;
	while (i < pipeline->len)
	{
		move_next_pipe(&pipes, i + 1 == pipeline->len);
		replace_stdio_fd(si, &pipes);
		fork_execute_command(&pipes, &pipeline->commands[i], &pipeline->childs[i]);
		i++;
	}
	ft_close(pipes.prev_pipe[0]);
	ft_close(pipes.prev_pipe[1]);
	return (wait_childs(pipeline));
}

int execute_single_cmd(t_pipeline *pipeline)
{
	t_builtin_types	type;

	if (handle_redirect(pipeline->commands->redir))
		return (1);
	type = is_builtin(pipeline->commands);
	if (type)
		return (execute_builtin(pipeline->commands->data.c, type));
	else if (pipeline->commands->type == C_SUBSHELL)
		return (execute_subshell(pipeline->commands->data.s));
	pipeline->childs[0] = fork();
	if (pipeline->childs[0] == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	else if (pipeline->childs[0] == 0)
		exit(execute_simple_cmd(pipeline->commands->data.c));
	return (wait_child(pipeline->childs[0]));
}

void execute_line(t_shell_info *si, t_command_node *node)
{
	while (node)
	{
		if (node->type == C_PIPELINE)
		{
			if (node->pipeline->len == 1)
				si->last_status = execute_single_cmd(node->pipeline);
			else
				si->last_status = execute_pipeline(si, node->pipeline);
			restore_default_fd(si);
		}
		else if (node->type == C_OR)
		{
			if (!si->last_status)
				node = node->next;
		}
		else if (node->type == C_AND)
		{
			if (si->last_status)
				node = node->next;
		}
		node = node->next;
	}
}