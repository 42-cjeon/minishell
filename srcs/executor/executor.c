/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:01:41 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 12:53:25 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "executor.h"
#include "parser.h"
#include "shell.h"
#include "libft.h"

void fork_execute_command(t_shell_info *si, t_pipes *pipes, t_command *command, pid_t *child)
{
	t_builtin_types	type;
	pid_t			pid;
	
	pid = fork();
	if (pid == -1)
		ft_perror_texit(PROJECT_NAME, 1);
	else if (pid == 0)
	{
		if (handle_redirect(si, command->redir))
			exit(1);
		close_pipes(pipes);
		type = is_builtin(command);
		if (type)
			exit(execute_builtin(si, command->data.c, type)); 
		else if (command->type == C_SUBSHELL)
			exit(execute_subshell(si, command->data.s));
		else /* type == C_COMMAND */
			execute_simple_cmd(si, command->data.c);
	}
	else if (pid > 0)
		*child = pid;
}

int execute_pipeline(t_shell_info *si, t_pipeline *pipeline)
{
	t_pipes	pipes;
	size_t	i;

	pipes_init(&pipes);
	move_next_pipe(&pipes, FALSE);
	replace_stdio_fd(si, &pipes);
	fork_execute_command(si, &pipes, &pipeline->commands[0], &pipeline->childs[0]);
	i = 1;
	while (i < pipeline->len)
	{
		move_next_pipe(&pipes, i + 1 == pipeline->len);
		replace_stdio_fd(si, &pipes);
		fork_execute_command(si, &pipes, &pipeline->commands[i], &pipeline->childs[i]);
		i++;
	}
	ft_close(pipes.prev_pipe[0]);
	ft_close(pipes.prev_pipe[1]);
	return (wait_childs(pipeline));
}

int execute_single_cmd(t_shell_info *si, t_pipeline *pipeline)
{
	t_builtin_types	type;

	if (handle_redirect(si, pipeline->commands->redir))
		return (1);
	type = is_builtin(pipeline->commands);
	if (type)
		return (execute_builtin(si, pipeline->commands->data.c, type));
	pipeline->childs[0] = fork();
	if (pipeline->childs[0] == -1)
		ft_perror_texit(PROJECT_NAME, 10);
	else if (pipeline->childs[0] == 0)
	{
		if (pipeline->commands->type == C_COMMAND)
			execute_simple_cmd(si, pipeline->commands->data.c);
		else if (pipeline->commands->type == C_SUBSHELL)
			execute_subshell(si, pipeline->commands->data.s);
	}
	return (wait_child(pipeline->childs[0]));
}

void execute_line(t_shell_info *si, t_command_node *node)
{
	while (node)
	{
		if (node->type == C_PIPELINE)
		{
			if (node->pipeline->len == 1)
				si->last_status = execute_single_cmd(si, node->pipeline);
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