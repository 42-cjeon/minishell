/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:11:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:49:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <dirent.h>

# include "tokenizer.h"

typedef enum e_expander_result
{
	EXP_SUCCESS = 0,
	EXP_CONTINUE = 1,
	EXP_JUMP = 2,
	EXP_STAY = 3,
	EXP_NOMATCH = 4,
	EXP_EMALLOC = -1
}	t_expander_result;

typedef struct s_expander_context
{
	t_tokenv		*tokenv;
	t_tokenv		*next_tokenv;
	t_token_node	*prev;
	t_token_node	*curr;
	t_token_node	*jump_to;
}	t_expander_context;

typedef struct s_str_node
{
	char	*str;
	size_t	len;
	struct s_str_node *next;
}	t_str_node;

typedef struct s_wildcard_info
{
	t_str_node	*wildcard;
	size_t		total_len;
	char		*first_token;
	char		*last_token;
	char		*basename;
	char		*nomatch;
}	t_wildcard_info;

typedef int	(*t_expander)(t_expander_context *context);

int	expand(t_tokenv *tokenv);
int	expand_word_splitting(t_expander_context *context);
int	expand_variable(t_expander_context *context);
int	expand_filename(t_expander_context *context);
int	merge_string_tokens(t_expander_context *context);
int del_space_node(t_expander_context *context);
int	handle_string(char *token, t_tokenv *tokenv);
int	handle_space(char *token, t_tokenv *tokenv);
int	handle_empty(char *token, t_tokenv *tokenv);
t_tokenv	*split_token(char *token);
void		get_wildcard_strs(t_expander_context *context, t_wildcard_info *wcinfo);
void		get_wildcard_info(t_expander_context *context, t_wildcard_info *wcinfo);
void		strv_clear(t_str_node *node);
t_str_node	*str_node_new(char *str);
void	str_node_push(t_wildcard_info *wcinfo, t_str_node **ptail, t_str_node *node);
void	wildcard_info_clear(t_wildcard_info *wcinfo);
void	add_first_token(t_wildcard_info *wcinfo, const char *path);
void	wildcard_push_last(t_wildcard_info *wcinfo, t_str_node **tail, t_str_node **last);
void move_next_token_node(t_expander_context *context);
void append_nomatch_str(t_wildcard_info *wcinfo, char *token);
void	append_last_token(t_wildcard_info *wcinfo, t_str_node *last);
t_bool match_part(t_str_node *str_node, const char *filename, \
		size_t filename_len, size_t left_char);
t_bool match_filename(t_wildcard_info *wcinfo, const char *filename);
int append_matched_for_each(DIR *ent, t_wildcard_info *wcinfo, \
		t_tokenv *filenames);
int append_matched(t_wildcard_info *wcinfo, t_tokenv *filenames);
void append_nomatch(t_wildcard_info *wcinfo, t_tokenv *tokenv);
t_bool exp_is_wildcard_start(t_token_node *curr, t_token_node *next);
t_bool exp_iswildcard(t_token_node *node);
t_expander_result	for_each_node(t_tokenv *tokenv, t_expander expander);
size_t	replace_variable(char **str, const size_t start);
#endif