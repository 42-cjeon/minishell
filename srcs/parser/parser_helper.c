/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/20 10:37:54 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"

int check_cmd_type(t_command *cmd, int curr_type)
{
	if (cmd->type == C_NONE)
	{
		if (curr_type == TK_STRING)
		{
			cmd->type = C_COMMAND;
			return (P_SUCCESS);
		}
		if (curr_type == TK_SUBSHELL)
		{
			cmd->type = C_SUBSHELL;
			return (P_SUCCESS);
		}
	}
	else if (cmd->type == C_SUBSHELL && curr_type == TK_STRING)
		return (P_ESYNTEX);
	else if (cmd->type == C_COMMAND && curr_type == TK_SUBSHELL)
		return (P_ESYNTEX);
	return (P_SUCCESS);
}