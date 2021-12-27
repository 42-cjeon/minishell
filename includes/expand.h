/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:11:09 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/25 17:16:54 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "tokenize.h"

typedef enum e_expander_result
{
	EXP_SUCCESS = 0,
	EXP_EMALLOC = -1
}	t_expander_result;

typedef struct s_expander_context
{
	t_tokenv		*tokenv;
	t_token_node	**prev;
	t_token_node	**curr;
}	t_expander_context;

typedef t_expander_result	(*t_expander)(t_expander_context *context);

t_tokenv *split_token(char *token);
t_expander_result	handle_empty(char *token, t_tokenv *tokenv);
t_expander_result	handle_space(char *token, t_tokenv *tokenv);
t_expander_result	handle_string(char *token, t_tokenv *tokenv);

char *ft_replace_str(char *str, size_t start, size_t len, char *with);
size_t	replace_variable(char **str, const size_t start);

t_expander_result	expand_variable(t_expander_context *context);
t_expander_result	expand(t_tokenv *tokenv);

#endif