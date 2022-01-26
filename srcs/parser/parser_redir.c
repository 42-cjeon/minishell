/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:10:55 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 16:33:02 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "tokenizer.h"
#include "utils.h"

int	parse_redir_in_target(t_token_node *curr, t_redir *redir)
{
	if (curr == NULL || curr->type != TK_STRING)
		return (P_ESYNTEX);
	move_string(&redir->target, &curr->token);
	return (P_SUCCESS);
}

int	parse_redir(t_token_node *curr, t_command *cmd)
{
	t_redir	*redir;
	int		result;

	redir = get_redir();
	push_redir(&cmd->redir, redir);
	if (curr->type == TK_REDIR_INPUT)
		redir->type = REDIR_IN;
	else if (curr->type == TK_REDIR_OUTPUT)
		redir->type = REDIR_OUT;
	else if (curr->type == TK_HEREDOC)
		redir->type = REDIR_HEREDOC;
	else
		redir->type = REDIR_APPEND;
	curr = curr->next;
	result = parse_redir_in_target(curr, redir);
	if (result != P_SUCCESS)
		clear_redir(&cmd->redir);
	return (result);
}

t_redir	*get_redir(void)
{
	t_redir	*redir;

	redir = ft_malloc(sizeof(t_redir));
	redir->next = NULL;
	redir->target = NULL;
	redir->type = REDIR_NONE;
	return (redir);
}
