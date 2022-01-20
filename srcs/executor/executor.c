/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:01:41 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 07:14:02 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "executor.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

extern char **environ;

int handle_redirect(t_redir *redir)
{
	int target_fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
	
			target_fd = open(redir->target, O_RDWR);
			dup2(target_fd, STDIN_FILENO);
			close(target_fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			target_fd = open(redir->target, O_WRONLY | O_CREAT, 0655);
			dup2(target_fd, STDOUT_FILENO);
			close(target_fd);
		}
		redir = redir->next;
	}
	return (0);
}

int restore_default_fd(t_shell_info *si)
{
	int fd[3];

	fd[STDIN_FILENO] = open(si->default_stdin, O_RDWR);
	fd[STDOUT_FILENO] = open(si->default_stdout, O_RDWR);
	fd[STDERR_FILENO] = open(si->default_stderr, O_RDWR);
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(fd[STDERR_FILENO], STDERR_FILENO);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	close(fd[STDERR_FILENO]);
	return 999;
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
	return (execve(cmd[0], cmd, environ));
}

int close_pipes(t_pipes *pipes)
{
	if (pipes->curr_pipe[0] != -1)
		close(pipes->curr_pipe[0]);
	if (pipes->curr_pipe[1] != -1)
		close(pipes->curr_pipe[1]);
	if (pipes->prev_pipe[0] != -1)
		close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		close(pipes->prev_pipe[1]);
	return (0);
}

void fork_execute_command(t_pipes *pipes, t_command *command, pid_t *child)
{
	t_builtin_types	type;
	pid_t	pid;
	
	handle_redirect(command->redir);
	pid = fork();
	if (pid == -1)
		exit(128);
	else if (pid == 0)
	{
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

t_bool is_lastidx(size_t i, size_t last)
{
	if (i + 1 == last)
		return (TRUE);
	return (FALSE);
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
		close(pipes->prev_pipe[0]);
	if (pipes->prev_pipe[1] != -1)
		close(pipes->prev_pipe[1]);
	pipes->prev_pipe[0] = pipes->curr_pipe[0];
	pipes->prev_pipe[1] = pipes->curr_pipe[1];
	if (!islast)
		pipe(pipes->curr_pipe);
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
		fd = open(si->default_stdin, O_RDWR);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		dup2(pipes->prev_pipe[0], STDIN_FILENO);
	if (pipes->curr_pipe[0] == -1)
	{
		fd = open(si->default_stdout, O_RDWR);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(pipes->curr_pipe[1], STDOUT_FILENO);
}

int wait_childs(t_pipeline *pipeline)
{
	size_t i;
	int status;

	i = 0;
	while (i < pipeline->len)
	{
		waitpid(pipeline->childs[i], &status, 0);
		i++;
	}
	return (status);
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
	close(pipes.prev_pipe[0]);
	close(pipes.prev_pipe[1]);
	
	return (wait_childs(pipeline));
}

int execute_single_cmd(t_pipeline *pipeline)
{
	t_builtin_types	type;
	int				status;

	handle_redirect(pipeline->commands->redir);
	type = is_builtin(pipeline->commands);
	if (type)
		return (execute_builtin(pipeline->commands->data.c, type));
	else if (pipeline->commands->type == C_SUBSHELL)
		return (execute_subshell(pipeline->commands->data.s));
	pipeline->childs[0] = fork();
	if (pipeline->childs[0] == -1)
		return (/*FORK_ERROR*/1);
	else if (pipeline->childs[0] == 0)
		exit(execute_simple_cmd(pipeline->commands->data.c));
	else
	{
		waitpid(pipeline->childs[0], &status, 0);
		return (status);
	}
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