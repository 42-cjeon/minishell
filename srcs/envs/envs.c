/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:40:17 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 22:56:53 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"
#include <stdlib.h>

t_envs	*envs_create(const char *envp[])
{
	t_envs	*ret;
	int		i;

	ret = ft_malloc(sizeof(t_envs));
	ret->lst = ft_llist_create((void (*)(void *))cenv_delete,
			(int (*)(const void *, const void *))cenv_compare,
			(void (*)(const void *))cenv_print);
	ret->bst = ft_bstree_create((void (*)(void *))cenv_delete,
			(int (*)(const void *, const void *))cenv_compare,
			(void (*)(void *))cenv_print_export);
	i = 0;
	while (envp[i] != NULL)
	{
		ft_llist_push_back(ret->lst,
			ft_llnode_create(cenv_create(envp[i])));
		ft_bstree_insert(ret->bst,
			ft_bstnode_create(cenv_create(envp[i])));
		++i;
	}
	return (ret);
}

void	envs_delete(t_envs *envs)
{
	if (envs)
	{
		ft_llist_delete(envs->lst);
		ft_bstree_delete(envs->bst);
		free(envs);
	}
}

void	envs_print(const t_envs *envs, t_print_order porder)
{
	if (porder == PORDER_UNSORTED)
		ft_llist_print(envs->lst);
	else if (porder == PORDER_SORTED)
		ft_bstree_print(envs->bst);
}

char	*envs_get_value(const t_envs *envs, const char *key)
{
	char		*ret;
	t_cenv		*cenv;
	t_bstnode	**pos;

	ret = NULL;
	cenv = cenv_create(key);
	pos = ft_bstree_search(envs->bst, cenv);
	if (*pos)
		ret = ((t_cenv *)((*pos)->content))->value;
	cenv_delete(cenv);
	return (ret);
}
