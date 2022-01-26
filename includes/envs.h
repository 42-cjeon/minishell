/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:40:22 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 12:37:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_H
# define ENVS_H

# include "libft.h"
# include "cenv.h"

typedef struct s_envs
{
	t_llist		*lst;
	t_bstree	*bst;
}	t_envs;

typedef enum e_print_order
{
	PORDER_UNSORTED = 0,
	PORDER_SORTED
}	t_print_order;

t_envs		*envs_create(const char *envp[]);
void		envs_delete(t_envs *envs);
void		envs_arr_delete(char **envs_arr);
void		envs_print(const t_envs *envs, t_print_order porder);
char		*envs_get_value(const t_envs *envs, const char *key);
char		**envs_to_arr(t_envs *envs);
void		envs_insert(const t_envs *envs, const char *str);
void		envs_erase(const t_envs *envs, const char *str);

#endif
