/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:34:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/11 20:11:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tokenize.h"
#include "parser.h"
#include "ft_perror.h"

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

int select_next_parser(t_token_node *tokenv)
{

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

int calc_pipeline_len(t_token_node *node)
{

}

int parse_subshell(t_parser_context *context)
{

}

int parse_redir_target(t_parser_context *context, t_redir_info *info)
{
	info->target = context->curr->token;
	context->curr = context->curr->next;
	return (P_SUCCESS);
}

int next_redir(t_parser_context *context, t_redir_info *info)
{
	context->curr = context->curr->next;
	if (context->curr == NULL)
		return (P_EUNEXPECTED_ENDL);
	else if (context->curr->type == TK_STRING)
		return (parse_redir_target(context, info));
	else
		return (P_ESYNTEX);
}

int parse_redir(t_parser_context *context, t_redir_info (*info)[2])
{
	if (context->curr->type == TK_REDIR_INPUT)
	{
		info[0]->type = REDIR_IN;
		return (next_redir(context, info[0]));
	}
	else if (context->curr->type == TK_REDIR_OUTPUT)
	{
		info[1]->type = REDIR_OUT;
		return (next_redir(context, info[1]));
	}
	else if (context->curr->type == TK_HEREDOC)
	{
		info[0]->type = REDIR_HEREDOC;
		return (next_redir(context, info[0]));
	}
	else if (context->curr->type == TK_APPEND)
	{
		info[1]->type = REDIR_APPEND;
		return (next_redir(context, info[1]));
	}
	else
		return (P_ESYNTEX);
}

int next_logical_oper(t_parser_context *context)
{
	t_token_type	type;

	context->curr = context->curr->next;
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
	if (context->curr)
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
	pipeline->childs = ft_malloc(sizeof(pid_t) * len);
	pipeline->pipes = ft_malloc(sizeof(t_pipe) * len);
	pipeline->commands = ft_malloc(sizeof(t_command) * len);
	return (pipeline);
}

size_t calc_command_len(t_token_node *node)
{
	size_t len;

	len = 0;
	while (node && node->type == TK_STRING)
	{
		len++;
		node = node->next;
	}
	return (len);
}

int parse_command(t_parser_context *context, t_command *command)
{	
	size_t index;

	command->type = C_COMMAND;
	command->data.c = ft_malloc(sizeof(char *) * (calc_command_len(context->curr) + 1));
	index = 0;
	while (context->curr && context->curr->type == TK_STRING)
	{
		command->data.c[index++] = context->curr->token;
		context->curr = context->curr->next;
	}
	command->data.c[index] = NULL;
	return (P_SUCCESS);
}

int next_pipeline(t_parser_context *context)
{
	context->curr = context->curr->next;
	if (context->curr == NULL)
		return (P_SUCCESS);
	if (tk_islogicaloper(context->curr->type))
		return (parse_logical_oper(context));
	return (P_ESYNTEX);
}

int parse_pipeline(t_parser_context *context)
{
	t_pipeline	*pipeline;
	size_t index;

	pipeline = get_pipeline(context->curr);
	index = 0;
	while (context->curr->type == TK_PIPE)
	{
		add_pipeline();
		contex
		index++;
	}
	if (context->curr->type == TK_SUBSHELL)
		pipeline->commands
	if (context->curr->type != TK_STRING)
	return (parse_logical_oper(context));
}

int parse(t_tokenv *tokenv, t_line_info *li)
{
	t_token_node *node;
	t_parser_context context;

	context.li = li;
	context.curr = tokenv->head;
	return parse_pipeline(&context);
}