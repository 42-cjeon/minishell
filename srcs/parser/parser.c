/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:34:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 15:50:51 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tokenizer.h"
#include "expander.h"
#include "parser.h"
#include "libft.h"
#include "shell.h"

int	parse(t_tokenv *tokenv, t_line_info *li)
{
	t_parser_context	context;

	context.li = li;
	context.curr = tokenv->head;
	return (parse_pipeline(&context));
}

t_command_node	*parse_line(t_shell_info *si, char *line)
{
	t_tokenv	tokenv;
	t_line_info	li;

	tokenv_init(&tokenv);
	if (tokenize(line, &tokenv) || expand(si, &tokenv) || lex(&tokenv))
	{
		tokenv_clear(&tokenv);
		return (NULL);
	}
	ft_memset(&li, 0, sizeof(t_line_info));
	if (parse(&tokenv, &li))
	{
		ft_perror_custom("minishell", "syntex error");
		tokenv_clear(&tokenv);
		command_node_clear(li.head);
		return (NULL);
	}
	tokenv_clear(&tokenv);
	return (li.head);
}
