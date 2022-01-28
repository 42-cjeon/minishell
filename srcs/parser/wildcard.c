/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:49:52 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 11:31:56 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

#include "expander.h"
#include "libft.h"
#include "tk_types.h"
#include "tokenizer.h"
#include "utils.h"

t_bool	match_part(t_str_node *str_node, const char *filename, \
			size_t filename_len, size_t left_char)
{
	if (left_char == 0 || str_node == NULL)
		return (TRUE);
	while (left_char <= filename_len)
	{
		if (streq_part(filename, str_node->str))
			if (match_part(str_node->next, filename + str_node->len, \
				filename_len - str_node->len, left_char - str_node->len))
				return (TRUE);
		if (match_part(str_node, filename + 1, filename_len - 1, left_char))
			return (TRUE);
		filename_len--;
	}
	return (FALSE);
}

t_bool	match_filename(t_wildcard_info *wcinfo, const char *filename)
{
	size_t	filename_len;
	size_t	first_len;
	size_t	last_len;

	first_len = ft_strlen(wcinfo->first_token);
	last_len = ft_strlen(wcinfo->last_token);
	filename_len = ft_strlen(filename);
	if (filename_len < wcinfo->total_len + first_len + last_len)
		return (FALSE);
	if (*filename == '.' && *wcinfo->first_token != '.')
		return (FALSE);
	if (!streq_part(filename, wcinfo->first_token) \
		|| !streq_part(filename + filename_len - last_len, wcinfo->last_token))
		return (FALSE);
	return (match_part(wcinfo->wildcard, filename + first_len, \
			filename_len - last_len, wcinfo->total_len));
}

int	append_matched_for_each(DIR *ent, t_wildcard_info *wcinfo, \
		t_tokenv *filenames)
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
			tokenv_assign_push(filenames, token, TK_STRING);
		}
		dir = readdir(ent);
	}
	if (errno)
		ft_perror_texit(PROJECT_NAME, 1);
	if (some_matched)
		return (EXP_SUCCESS);
	return (EXP_NOMATCH);
}

int	append_matched(t_wildcard_info *wcinfo, t_tokenv *filenames)
{
	DIR	*ent;
	int	result;

	if (*wcinfo->basename)
		ent = opendir(wcinfo->basename);
	else
		ent = opendir("./");
	if (ent == NULL)
	{
		if (errno == ENOENT || errno == EACCES)
			return (EXP_NOMATCH);
		ft_perror_texit(PROJECT_NAME, 1);
	}
	result = append_matched_for_each(ent, wcinfo, filenames);
	if (closedir(ent))
		ft_perror_texit(PROJECT_NAME, 1);
	return (result);
}

void	append_nomatch(t_wildcard_info *wcinfo, t_tokenv *tokenv)
{
	char			*token;
	t_token_node	*node;

	token = ft_strdup(wcinfo->nomatch);
	node = token_node_new(token, TK_STRING);
	tokenv->head = node;
	tokenv->tail = node;
}
