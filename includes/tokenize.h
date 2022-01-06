/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:40:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/05 05:39:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stddef.h>
# include "tk_types.h"

typedef enum e_tokenizer_result
{
	TKZR_SUCCESS = 0,
	TKZR_EMALLOC = -1,
	TKZR_EUNEXPECTEDNL = -2
}	t_tokenizer_result;

typedef enum e_token_type
{
	TK_UNESCAPED_STRING,
	TK_QUOTED_STRING,
	TK_DQUOTED_STRING,
	TK_SPACE,
	TK_SUBSHELL,
	TK_OPERATOR,
	TK_WILDCARD,
	TK_STRING,
	TK_COMMAND,
	TK_ARG,
	TK_HEREDOC,
	TK_REDIR_INPUT,
	TK_REDIR_OUTPUT,
	TK_APPEND,
	TK_OR,
	TK_AND,
	TK_PIPE
}	t_token_type;

typedef struct s_token_node
{
	char *token;
	t_token_type type;
	struct s_token_node *next;
}	t_token_node;

typedef struct s_tokenv
{
	t_token_node *head;
	t_token_node *tail;
}	t_tokenv;

typedef struct s_tokenizer_context
{
	t_tokenv	*tokenv;
	const char	*raw_line;
	size_t		cursor;
}	t_tokenizer_context;

t_bool	context_peek_cmp(t_tokenizer_context *context, \
							t_tk_typecmp tk_typecmp);
size_t	seek_first_nq(t_tokenizer_context *context, t_tk_typecmp tk_typecmp);
size_t	seek_first_eq(t_tokenizer_context *context, t_tk_typecmp tk_typecmp);
size_t	seek_first_nq_op(t_tokenizer_context *context);

void	tokenv_push(t_tokenv *tokenv, t_token_node *new);
int		tokenv_assign_push(t_tokenv *tokenv, char *token, t_token_type type);
t_token_node *token_node_new(char *token, t_token_type type);
void	tokenv_init(t_tokenv *tokenv);
void	tokenv_clear(t_tokenv *tokenv);

t_tokenizer_result	tokenize_wildcard(t_tokenizer_context *context);
t_tokenizer_result	select_next_tokenizer(t_tokenizer_context *context);
t_tokenizer_result	tokenize_unescaped(t_tokenizer_context *context);
t_tokenizer_result	tokenize_quote(t_tokenizer_context *context);
t_tokenizer_result	tokenize_dquote(t_tokenizer_context *context);
t_tokenizer_result	tokenize_space(t_tokenizer_context *context);
t_tokenizer_result	tokenize_subshell(t_tokenizer_context *context);
t_tokenizer_result	tokenize_operator(t_tokenizer_context *context); 
t_tokenizer_result	tokenize(const char *raw_line, t_tokenv *tokenv);

#endif