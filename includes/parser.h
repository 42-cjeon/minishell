/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:36:34 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/11 11:21:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include "tokenize.h"

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

typedef enum e_command_node_type
{
	C_OR,
	C_AND,
	C_PIPELINE
}	t_command_node_type;

typedef struct s_redir_info
{
	t_redir_type	in_type;
	char			*in_target;
	t_redir_type	out_type;
	char			*out_target;
}	t_redir_info;

typedef int  t_pipe[2];
typedef char **t_command;

typedef struct s_pipeline
{
	size_t		length;
	pid_t		*childs;
	t_pipe		*pipes;
	t_command	*commands;
}	t_pipeline;

typedef struct s_command_node
{
	t_command_node_type		type;
	t_pipeline				pipeline;
	t_redir_info			redir_info;
	struct s_command_node	*next;
}	t_command_node;

typedef struct s_line_info
{
	t_command_node *head;
	t_command_node *tail;
}	t_line_info;

typedef struct s_parser_context
{
	t_token_node *curr;
	t_line_info *li;

}	t_parser_context;

#endif