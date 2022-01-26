/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:36:34 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 17:49:11 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>

# include "shell.h"
# include "tokenizer.h"

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

typedef int	t_pipe[2];

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
	t_command_node	*head;
	t_command_node	*tail;
}	t_line_info;

typedef struct s_parser_context
{
	t_token_node	*curr;
	t_line_info		*li;
}	t_parser_context;

int				lex(t_tokenv *tokenv);
int				parse_command(t_parser_context *context, t_command *cmd);
int				validate_command(t_token_node *curr, t_command *cmd);
t_command_node	*get_cmd_node(t_command_node_type type, t_pipeline *pipeline);
void			push_line_info(t_line_info *li, t_command_node *node);
int				clear_pipeline(t_parser_context *context);
void			push_redir(t_redir **head, t_redir *new);
void			clear_redir(t_redir **head);
int				check_cmd_type(t_command *cmd, int curr_type);
int				next_logical_oper(t_parser_context *context);
int				parse_logical_oper(t_parser_context *context);
int				parse_pipeline(t_parser_context *context);
int				next_pipeline(t_parser_context *context);
int				parse_pipe(t_parser_context *context, int is_last);
t_pipeline		*get_pipeline(t_token_node *node);
int				parse_redir_in_target(t_token_node *curr, t_redir *redir);
int				parse_redir(t_token_node *curr, t_command *cmd);
t_redir			*get_redir(void);
int				parse(t_tokenv *tokenv, t_line_info *li);
t_command_node	*parse_line(t_shell_info *si, char *line);
void			line_info_clear(t_line_info *li);
void			command_node_clear(t_command_node *node);
void			pipeline_clear(t_pipeline *pipeline);
void			command_clear(t_command *commands, size_t len);
void			data_clear(t_cmd_data data, int type);
void			redir_clear(t_redir *redir);

#endif