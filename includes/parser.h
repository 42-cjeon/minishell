/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:36:34 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/07 05:44:03 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H



typedef union u_ast_child
{

}	t_ast_child;

typedef struct s_ast_node
{
	t_ast_child	*child;
	t_ast_type	*type;
}	t_ast_node;

typedef struct s_ast
{
	t_ast_node	*head;
	t_ast_node	*tail;
}	t_ast;

#endif