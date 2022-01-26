/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:06:18 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:27:23 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

void	redir_clear(t_redir *redir)
{
	t_redir	*curr;
	t_redir	*next;

	curr = redir;
	while (curr)
	{
		next = curr->next;
		free(curr->target);
		free(curr);
		curr = next;
	}
}

void	data_clear(t_cmd_data data, int type)
{
	char	**cmd_arr;

	if (type == C_SUBSHELL)
		free(data.s);
	else
	{
		cmd_arr = data.c;
		while (*cmd_arr)
			free(*cmd_arr++);
		free(data.c);
	}
}

void	command_clear(t_command *commands, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		redir_clear(commands[i].redir);
		data_clear(commands[i].data, commands[i].type);
		i++;
	}
	free(commands);
}
