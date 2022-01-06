/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/5 00:08:39 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/02 20:00:31 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "libft.h"
#include "expand.h"
#include "tokenize.h"
#include "exp_types.h"
#include "tk_types.h"


#include <stdio.h>
void print_tk(t_tokenv *v)
{
	t_token_node *node;

	node = v->head;
	while (node)
	{
		printf("TK=[%s]\n", node->token);
		node = node->next;
	}
}

t_bool find_last_slash(const char *path, size_t *last_slash, size_t *len)
{
	size_t	i;
	size_t	last_found;
	t_bool	found;

	found = FALSE;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			found = TRUE;
			last_found = i;
		}		
		i++;
	}
	*len = i;
	if (found)
		*last_slash = last_found;
	return (found);
}

typedef struct s_add_first_token
{
	t_wildcard_info *wcinfo;
}	t_add_first_token;

int _add_first_token(t_add_first_token *var, int result)
{
	if (result)
	{
		free(var->wcinfo->basename);
		free(var->wcinfo->first_token);
		var->wcinfo->basename = NULL;
		var->wcinfo->first_token = NULL;
	}
	return (result);
}

int	add_first_token(t_wildcard_info *wcinfo, const char *path)
{
	size_t 	path_len;
	size_t	last_slash;

	if (path == NULL)
	{
		wcinfo->basename = ft_strdup("");
		wcinfo->first_token = ft_strdup("");
		wcinfo->nomatch = ft_strdup("*");
	}
	else if (!find_last_slash(path, &last_slash, &path_len))
	{
		wcinfo->basename = ft_strdup("");
		wcinfo->first_token = ft_strdup(path);
		wcinfo->nomatch = ft_strdup(path);
	}
	else
	{
		wcinfo->basename = ft_substr(path, 0, last_slash + 1);
		wcinfo->first_token = ft_substr(path, last_slash + 1, \
											path_len - last_slash);
		wcinfo->nomatch = ft_strdup(path);
	}
	return (wcinfo->basename == NULL || wcinfo->basename == NULL \
			|| wcinfo->nomatch == NULL);
}

typedef struct s_get_filenames
{
	t_tokenv		*filenames;
	t_wildcard_info	*wcinfo;
} t_get_filenames;

void strv_clear(t_str_node *node)
{
	t_str_node *next;

	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

int str_node_new(char *str, t_str_node **result)
{
	t_str_node *node;

	node = malloc(sizeof(t_str_node));
	if (node == NULL)
		return (1);
	node->str = str;
	node->len = ft_strlen(str);
	node->next = NULL;
	*result = node;
	return (0);
}

void	str_node_push(t_wildcard_info *wcinfo, t_str_node **ptail, t_str_node *node)
{
	if (*ptail == NULL)
	{
		wcinfo->wildcard = node;
		*ptail = node;
	}
	else
	{
		(*ptail)->next = node;
		*ptail = node;
	}
	wcinfo->total_len += node->len;
}

int ft_strcmp_part(const char *heystack, const char *needle)
{
	while (*needle != '\0')
		if (*heystack++ != *needle++)
			return (0);
	return (1);
}

int match_part(t_str_node *str_node, const char *filename, size_t filename_len, size_t left_char)
{
	if (left_char == 0 || str_node == NULL)
		return (1);
	while (left_char <= filename_len)
	{
		if (ft_strcmp_part(filename, str_node->str))
			if (match_part(str_node->next, filename + str_node->len, filename_len - str_node->len, left_char - str_node->len))
				return (1);
		if (match_part(str_node, filename + 1, filename_len - 1, left_char))
			return (1);
		filename_len--;
	}
	return (0);
}

int match_filename(t_wildcard_info *wcinfo, const char *filename)
{
	size_t	filename_len;
	size_t	first_len;
	size_t	last_len;

	first_len = ft_strlen(wcinfo->first_token);
	last_len = ft_strlen(wcinfo->last_token);
	filename_len = ft_strlen(filename);
	if (filename_len < wcinfo->total_len + first_len + last_len)
		return (0);
	if (!ft_strncmp(filename, ".", ft_strlen(filename)) || !ft_strncmp(filename, "..", ft_strlen(filename)))
		return (0);
	if (*filename == '.' && *wcinfo->first_token != '.')
		return (0);
	if (!ft_strcmp_part(filename, wcinfo->first_token) || !ft_strcmp_part(filename + filename_len - last_len, wcinfo->last_token))
		return (0);
	return (match_part(wcinfo->wildcard, filename + first_len, filename_len - last_len, wcinfo->total_len));
}

int append_matched_for_each(DIR *ent, t_wildcard_info *wcinfo, t_tokenv *filenames)
{
	char			*token;
	t_bool			some_matched;
	struct dirent	*dir;

	some_matched = FALSE;
	dir = readdir(ent);
	while (dir)
	{
		if (match_filename(wcinfo, dir->d_name))
		{
			some_matched = TRUE;
			token = ft_strjoin(wcinfo->basename, dir->d_name);
			if (token == NULL)
				return (EXP_EMALLOC);
			if (tokenv_assign_push(filenames, token, TK_STRING))
				return (EXP_EMALLOC);
		}
		dir = readdir(ent);
	}
	if (some_matched)
		return (EXP_SUCCESS);
	return (EXP_NOMATCH);
}

int append_matched(t_wildcard_info *wcinfo, t_tokenv *filenames)
{
	DIR	*ent;
	int	result;

	if (*wcinfo->basename)
		ent = opendir(wcinfo->basename);
	else
		ent = opendir("./");
	if (ent == NULL)
	{
		if (errno == ENOENT)
			return (EXP_NOMATCH);
		return (EXP_EMALLOC);
	}
	result = append_matched_for_each(ent, wcinfo, filenames);
	closedir(ent);
	if (result == EXP_EMALLOC)
		tokenv_clear(filenames);
	return (result);
}

//FIX

//int get

t_bool exp_is_wildcard_start(t_token_node *curr, t_token_node *next)
{
	if (curr->type == TK_WILDCARD)
		return (TRUE);
	if (curr->type == TK_STRING && next && next->type == TK_WILDCARD)
		return (TRUE);
	return (FALSE);
}

int append_nomatch(t_wildcard_info *wcinfo, t_tokenv *tokenv)
{
	char			*token;
	t_token_node	*node;

	token = ft_strdup(wcinfo->nomatch);
	if (token == NULL)
		return (EXP_EMALLOC);
	node = token_node_new(token, TK_STRING);
	if (node == NULL)
	{
		free(token);
		return (EXP_EMALLOC);
	}
	tokenv->head = node;
	tokenv->tail = node;
	return (EXP_SUCCESS);
}

t_bool exp_iswildcard(t_token_node *node)
{
	if (node == NULL)
		return (FALSE);
	return (node->type == TK_STRING || node->type == TK_WILDCARD);
}

void wildcard_push_last(t_wildcard_info *wcinfo, t_str_node **tail, t_str_node **last)
{
	if (*last)
		str_node_push(wcinfo, tail, *last);
	*last = NULL;
}

void move_next_token_node(t_expander_context *context, int new_node_fail)
{
	context->prev->next = context->curr->next;
	if (new_node_fail)
		free(context->curr->token);
	free(context->curr);
	context->curr = context->prev->next;
}

int append_nomatch_str(t_wildcard_info *wcinfo, char *token)
{
	char *new_str;

	new_str = ft_strjoin(wcinfo->nomatch, token);
	if (new_str == NULL)
		return (1);
	free(wcinfo->nomatch);
	wcinfo->nomatch = new_str;
	return (0);
}

int append_last_token(t_wildcard_info *wcinfo, t_str_node *last)
{
	if (last)
		wcinfo->last_token = last->str;
	else
		wcinfo->last_token = ft_strdup("");
	free(last);
	if (wcinfo->last_token == NULL)
		return (EXP_EMALLOC);
	return (EXP_SUCCESS);
}

int get_wildcard_strs(t_expander_context *context, t_wildcard_info *wcinfo)
{
	t_str_node	*tail;
	t_str_node	*last;
	int			nomatch_fail;
	int			new_node_fail;

	tail = NULL;
	last = NULL;
	new_node_fail = 0;
	nomatch_fail = 0;
	while (exp_iswildcard(context->curr))
	{
		wildcard_push_last(wcinfo, &tail, &last);
		if (context->curr->type == TK_STRING)
		{
			new_node_fail = str_node_new(context->curr->token, &last);
			nomatch_fail = append_nomatch_str(wcinfo, \
				context->curr->token);
		}
		else
			nomatch_fail = append_nomatch_str(wcinfo, "*");
		move_next_token_node(context, new_node_fail);
		if (new_node_fail || nomatch_fail)
			return (EXP_EMALLOC);
	}
	return (append_last_token(wcinfo, last));
}

void wildcard_info_clear(t_wildcard_info *wcinfo)
{
	free(wcinfo->basename);
	free(wcinfo->first_token);
	free(wcinfo->last_token);
	free(wcinfo->nomatch);
	strv_clear(wcinfo->wildcard);
}

int _get_wildcard_info(t_wildcard_info *wcinfo, int status)
{
	if (status)
		wildcard_info_clear(wcinfo);
	return (status);
}

int	get_wildcard_info(t_expander_context *context, t_wildcard_info *wcinfo)
{
	if (add_first_token(wcinfo, context->curr->token))
		return (_get_wildcard_info(wcinfo, EXP_EMALLOC));
	context->prev->next = context->curr->next;
	free(context->curr->token);
	free(context->curr);
	context->curr = context->prev->next;
	if (get_wildcard_strs(context, wcinfo))
		return (_get_wildcard_info(wcinfo, EXP_EMALLOC));
	return (_get_wildcard_info(wcinfo, EXP_SUCCESS));
}

t_expander_result	expand_filename(t_expander_context *context)
{
	t_tokenv		matched;
	t_wildcard_info	wcinfo;
	int				result;

	if (!exp_is_wildcard_start(context->curr, context->curr->next))
		return (EXP_CONTINUE);
	ft_memset(&wcinfo, 0, sizeof(t_wildcard_info));
	if (get_wildcard_info(context, &wcinfo))
		return (EXP_EMALLOC);
	ft_memset(&matched, 0, sizeof(t_tokenv));
	result = append_matched(&wcinfo, &matched);
	if (result == EXP_EMALLOC)
		return (EXP_EMALLOC);
	else if (result == EXP_NOMATCH)
		if (append_nomatch(&wcinfo, &matched))
			return (EXP_EMALLOC);
	context->prev->next = matched.head;
	matched.tail->next = context->curr;
	return (EXP_STAY);
}

t_expander_result	expand_word_splitting(t_expander_context *context)
{
	t_tokenv *splited_tokenv;

	if (context->curr->type != TK_UNESCAPED_STRING)
		return (EXP_CONTINUE);
	splited_tokenv = split_token(context->curr->token);
	if (splited_tokenv == NULL)
		return (EXP_EMALLOC);
	if (context->prev == NULL)
		context->tokenv->head = splited_tokenv->head;
	else
		context->prev->next = splited_tokenv->head;
	splited_tokenv->tail->next = context->curr->next;
	context->jump_to = context->curr->next;
	free(context->curr->token);
	free(context->curr);
	free(splited_tokenv);
	return (EXP_JUMP);
}

t_expander_result	expand_variable(t_expander_context *context)
{
	size_t	cursor;
	size_t	len;

	if (context->curr->type != TK_DQUOTED_STRING \
		&& context->curr->type != TK_UNESCAPED_STRING)
		return (EXP_CONTINUE);
	cursor = 0;
	while (context->curr->token[cursor] != '\0')
	{
		if (exp_isdollarsign(context->curr->token[cursor]))
		{
			len = replace_variable(&context->curr->token, cursor);
			if (len == 0)
				return (EXP_EMALLOC);
			cursor += len;
		}
		else
			cursor++;
	}
	return (EXP_CONTINUE);
}

t_bool	tk_isstringtype(const t_token_type type)
{
	return (type == TK_QUOTED_STRING \
			|| type == TK_DQUOTED_STRING \
			|| type == TK_UNESCAPED_STRING);
}

t_expander_result	merge_string_tokens(t_expander_context *context)
{
	char			*merged_token;
	t_token_node	*next;

	next = context->curr->next;
	if (tk_isstringtype(context->curr->type))
		context->curr->type = TK_STRING;
	if (context->curr->type != TK_STRING \
		|| next == NULL || !tk_isstringtype(next->type))
		return (EXP_CONTINUE);
	merged_token = ft_strjoin(context->curr->token, next->token);
	if (merged_token == NULL)
		return (EXP_EMALLOC);
	free(context->curr->token);
	free(next->token);
	context->curr->next = next->next;
	free(next);
	context->curr->token = merged_token;
	return (EXP_STAY);
}

t_expander_result del_space_node(t_expander_context *context)
{
	if (context->curr->type != TK_SPACE)
		return (EXP_CONTINUE);
	
	context->jump_to = context->curr->next;
	if (context->prev == NULL)
		context->tokenv->head = context->jump_to;
	else
		context->prev->next = context->jump_to;
	free(context->curr);
	return (EXP_JUMP);
}

t_expander_result	for_each_node(t_tokenv *tokenv, t_expander expander)
{
	t_expander_context	context;
	t_expander_result	result;

	context.tokenv = tokenv;
	context.prev = NULL;
	context.curr = tokenv->head;
	while (context.curr)
	{
		result = expander(&context);
		if (result != EXP_STAY)
			context.prev = context.curr;
		if (result == EXP_CONTINUE)
			context.curr = context.curr->next;
		else if (result == EXP_JUMP)
			context.curr = context.jump_to;
		else if (result == EXP_STAY)
			context.curr = context.curr;
		else
			return (result);
	}
	return (EXP_SUCCESS);
}

t_expander_result	expand(t_tokenv *tokenv)
{
	t_expander_result	result;

	result = for_each_node(tokenv, expand_variable);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(tokenv, expand_word_splitting);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(tokenv, merge_string_tokens);
	if (result != EXP_SUCCESS)
		return (result);
	result = for_each_node(tokenv, expand_filename);
	if (result != EXP_SUCCESS)
		return (result);
	for_each_node(tokenv, del_space_node);
	return (EXP_SUCCESS);
}
