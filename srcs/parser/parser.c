/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:34:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 15:16:31 by cjeon            ###   ########.fr       */
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

int	parse_line(t_shell_info *si, char *line, t_line_info *li)
{
	t_tokenv	tokenv;

	tokenv_init(&tokenv);
	if (tokenize(line, &tokenv) || expand(si, &tokenv) || lex(&tokenv))
	{
		tokenv_clear(&tokenv);
		return (P_ESYNTEX);
	}
	if (tokenv.head == NULL)
		return (P_EMPTY);
	if (parse(&tokenv, li))
	{
		tokenv_clear(&tokenv);
		return (P_ESYNTEX);
	}
	tokenv_clear(&tokenv);
	return (P_SUCCESS);
}
