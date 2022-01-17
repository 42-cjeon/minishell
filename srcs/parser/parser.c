/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:34:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/16 19:14:36 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenize.h"
#include "parser.h"

int throw_syntax_error(const char *token)
{
	char	msg_buffer[51];
	int		msg_len;

	ft_strlcpy(msg_buffer, "minishell: syntax error near unexpected token `", 51);
	ft_strlcat(msg_buffer, token, 51);
	msg_len = ft_strlcat(msg_buffer, "'", 51);
	write(2, msg_buffer, msg_len - 1);
	return (P_ESYNTEX);
}

int throw_unexpected_endl(void)
{
	//sdfsddf
	return (P_EUNEXPECTED_ENDL);
}

t_bool tk_isredir(t_token_type type)
{
	return (type == TK_HEREDOC || type == TK_REDIR_INPUT
		|| type == TK_REDIR_OUTPUT || type == TK_APPEND);
}

t_bool tk_islogicaloper(t_token_type type)
{
	return (type == TK_AND || type == TK_OR);
}

void move_string(char **dst, char **src)
{
	*dst = *src;
	*src = NULL;
}

t_pipeline *get_pipeline(t_token_node *node)
{
	size_t	len;
	t_pipeline *pipeline;

	len = 1;
	while (node)
	{
		if (node->type == TK_PIPE)
			len++;
		node = node->next;
	}
	pipeline = ft_malloc(sizeof(t_pipeline));
	pipeline->len = len;
	pipeline->childs = ft_calloc(len, sizeof(pid_t));
	pipeline->pipes = ft_calloc(len, sizeof(t_pipe));
	pipeline->commands = ft_calloc(len, sizeof(t_command));
	return (pipeline);
}

void push_line_info(t_line_info *li, t_command_node *node)
{
	if (li->head == NULL)
	{
		li->head = node;
		li->tail = node;
	}
	else
	{
		li->tail->next = node;
		li->tail = node;
	}
}

void push_redir(t_redir **head, t_redir *new)
{
	t_redir *curr;

	curr = *head;
	if (curr == NULL)
		*head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_redir *get_redir(void)
{
	t_redir *redir;

	redir = ft_malloc(sizeof(t_redir));
	redir->next = NULL;
	redir->target = NULL;
	redir->type = REDIR_NONE;

	return (redir);
}

void	clear_redir(t_redir **head)
{
	t_redir *curr;
	t_redir *next;

	curr = *head;
	while (curr)
	{
		next = curr->next;
		free(curr->target);
		free(curr);
		curr = curr->next;
	}
	*head = NULL;
}

int parse_redir_in_target(t_token_node *curr, t_redir *redir)
{
	if (curr == NULL || curr->type != TK_STRING)
		return (P_ESYNTEX);
	move_string(&redir->target, &curr->token);
	return (P_SUCCESS);
}

int parse_redir(t_token_node *curr, t_command *cmd)
{
	t_redir	*redir;
	int		result;

	redir = get_redir();
	push_redir(&cmd->redir, redir);
	if (curr->type == TK_REDIR_INPUT)
		redir->type = REDIR_IN;
	else if (curr->type == TK_REDIR_OUTPUT)
		redir->type = REDIR_OUT;
	else if (curr->type == TK_HEREDOC)
		redir->type = REDIR_HEREDOC;
	else
		redir->type = REDIR_APPEND;
	curr = curr->next;
	result = parse_redir_in_target(curr, redir);
	if (result != P_SUCCESS)
		clear_redir(&cmd->redir);
	return (result);	
}

int check_cmd_type(t_command *cmd, int curr_type)
{
	if (cmd->type == C_NONE)
	{
		if (curr_type == TK_STRING)
		{
			cmd->type = C_COMMAND;
			return (P_SUCCESS);
		}
		if (curr_type == TK_SUBSHELL)
		{
			cmd->type = C_SUBSHELL;
			return (P_SUCCESS);
		}
	}
	else if (cmd->type == C_SUBSHELL && curr_type == TK_STRING)
		return (P_ESYNTEX);
	else if (cmd->type == C_COMMAND && curr_type == TK_SUBSHELL)
		return (P_ESYNTEX);
	return (P_SUCCESS);
}

int validate_command(t_token_node *curr, t_command *cmd)
{
	size_t cmd_len;
	int		result;

	cmd_len = 0;
	while (curr && (curr->type == TK_SUBSHELL || curr->type == TK_STRING \
		|| tk_isredir(curr->type)))
	{
		if (check_cmd_type(cmd, curr->type) != P_SUCCESS)
			return (P_ESYNTEX);
		if (tk_isredir(curr->type))
		{
			result = parse_redir(curr, cmd);
			if (result != P_SUCCESS)
				return (result);
		}
		else
			cmd_len++;
		curr = curr->next;
	}
	if (cmd->type == C_COMMAND)
	{
		cmd->data.c = ft_malloc(sizeof(char *) * (cmd_len + 1));
		cmd->data.c[cmd_len] = NULL;
	}
	return (P_SUCCESS);
}

int parse_command(t_parser_context *context, t_command *cmd)
{
	size_t	i;
	if (validate_command(context->curr, cmd) != P_SUCCESS)
		return (P_ESYNTEX);
	i = 0;
	while (context->curr && (context->curr->type == TK_SUBSHELL \
		|| context->curr->type == TK_STRING \
		|| tk_isredir(context->curr->type)))
	{
		if (tk_isredir(context->curr->type))
			context->curr = context->curr->next;
		else if (cmd->type == C_COMMAND)
			move_string(&cmd->data.c[i++], &context->curr->token);
		else if (cmd->type == C_SUBSHELL)
			move_string(&cmd->data.s, &context->curr->token);
		context->curr = context->curr->next;
	}
	return (P_SUCCESS);
}

int clear_pipeline(t_parser_context *context)
{
	(void)context;
	return (P_ESYNTEX);
}

t_command_node *get_cmd_node(t_command_node_type type, t_pipeline *pipeline)
{
	t_command_node *node;

	node = ft_malloc(sizeof(t_command_node));
	node->type = type;
	node->pipeline = pipeline;
	node->next = NULL;
	return (node);
}

int next_logical_oper(t_parser_context *context)
{
	t_token_type	type;

	if (context->curr == NULL)
		return (P_EUNEXPECTED_ENDL);
	type = context->curr->type;
	if (type == TK_SUBSHELL || type == TK_STRING \
		|| tk_isredir(type))
		return (parse_pipeline(context));
	return (P_ESYNTEX);
}

int parse_logical_oper(t_parser_context *context)
{
	t_command_node *node;

	if (context->curr->type == TK_AND)
		node = get_cmd_node(C_AND, NULL);
	else
		node = get_cmd_node(C_OR, NULL);
	context->curr = context->curr->next;
	push_line_info(context->li, node);
	return (next_logical_oper(context));
}

int parse_pipe(t_parser_context *context, int is_last)
{
	if (is_last)
	{
		if (context->curr == NULL)
			return (P_SUCCESS);
		if (context->curr->type == TK_PIPE)
			return (P_ESYNTEX);
		context->curr = context->curr->next;
		return (P_SUCCESS);
	}
	else
	{
		if (context->curr == NULL)
			return (P_ESYNTEX);
		if (context->curr->type != TK_PIPE)
			return (P_ESYNTEX);
		context->curr = context->curr->next;
		return (P_SUCCESS);
	}
}

int next_pipeline(t_parser_context *context)
{
	if (context->curr == NULL)
		return (P_SUCCESS);
	if (tk_islogicaloper(context->curr->type))
		return (parse_logical_oper(context));
	return (P_ESYNTEX);
}

int parse_pipeline(t_parser_context *context)
{
	t_pipeline *pipeline;
	size_t index;
	int result;

	pipeline = get_pipeline(context->curr);
	index = 0;
	while (index < pipeline->len)
	{
		result = parse_command(context, &pipeline->commands[index]);
		if (result != P_SUCCESS)
			break ;
		result = parse_pipe(context, index + 1 == pipeline->len);
		if (result != P_SUCCESS)
			break ;
		index++;
	}
	if (result != P_SUCCESS)
		return (clear_pipeline(context));
	push_line_info(context->li, get_cmd_node(C_PIPELINE, pipeline));
	return (next_pipeline(context));
}

int parse(t_tokenv *tokenv, t_line_info *li)
{
	t_parser_context context;

	context.li = li;
	context.curr = tokenv->head;
	return parse_pipeline(&context);
}
