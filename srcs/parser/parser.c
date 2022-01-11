/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:34:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/11 11:20:54 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tokenize.h"
#include "parser.h"

int select_next_parser(t_token_node *tokenv)
{

}

t_bool tk_isredir(t_token_type type)
{
	return (type == TK_HEREDOC || type == TK_REDIR_INPUT
		|| type == TK_REDIR_OUTPUT || type == TK_APPEND);
}

int parse_command()
{

}

int calc_pipeline_len(t_token_node *node)
{

}

int parse_pipeline(t_parser_context *context)
{
	t_pipeline	*pipeline;


}

int parse_redir(t_parser_context *context)
{

}

int parse_logical_oper(t_parser_context *context)
{

}

int parse_error(t_parser_context *context)
{

}

int parse(t_tokenv *tokenv, t_line_info *li)
{
	t_token_node *node;

	node = tokenv->head;
	if (node->type == TK_STRING)
		return (parse_string());
	else if (node->type == TK_SUBSHELL)
		return (parse_subshell());
	else if (tk_isredir(node->type))
		return (parse_redir());
	else
		return (parse_error());
}