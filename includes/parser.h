/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:36:34 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/16 17:13:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include "tokenize.h"

typedef enum e_parser_result
{
	P_SUCCESS,
	P_ESYNTEX,
	P_EUNEXPECTED_ENDL
}	t_parser_result;

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

typedef enum e_command_type
{
	C_NONE,
	C_COMMAND,
	C_SUBSHELL
}	t_command_type;

typedef enum e_command_node_type
{
	C_OR,
	C_AND,
	C_PIPELINE
}	t_command_node_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef int  t_pipe[2];

typedef union u_cmd_data
{
	char	**c;
	char	*s;
}	t_cmd_data;

typedef struct s_command
{
	int			type;
	t_redir		*redir;
	t_cmd_data	data;
}	t_command;

typedef struct s_pipeline
{
	size_t		len;
	pid_t		*childs;
	t_pipe		*pipes;
	t_command	*commands;
}	t_pipeline;

typedef struct s_command_node
{
	t_command_node_type		type;
	t_pipeline				*pipeline;
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

int parse_pipeline(t_parser_context *context);
int next_pipeline(t_parser_context *context);
int parse_logical_oper(t_parser_context *context);
int parse(t_tokenv *tokenv, t_line_info *li);
#endif