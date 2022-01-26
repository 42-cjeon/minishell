/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 03:31:35 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 15:08:55 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"
#include <stdlib.h>

static char	*str_make(const char *key, const char *value)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	ret = ft_strjoin(tmp, value);
	free(tmp);
	return (ret);
}

char	**envs_to_arr(t_envs *envs)
{
	char		**ret;
	t_llnode	*cur;
	char		*key;
	char		*value;
	int			i;

	ret = (char **)ft_malloc((envs->lst->size + 1) * sizeof(char *));
	cur = envs->lst->first;
	i = 0;
	while ((cur != NULL) && (i < envs->lst->size))
	{
		key = ((t_cenv *)(cur->content))->key;
		value = ((t_cenv *)(cur->content))->value;
		ret[i] = str_make(key, value);
		cur = cur->next;
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

void	envs_insert(const t_envs *envs, const char *str)
{
	t_cenv	*cenv;

	cenv = cenv_create(str);
	if (cenv->value)
		ft_llist_push(envs->lst, ft_llnode_create(cenv_create(str)));
	ft_bstree_insert(envs->bst, ft_bstnode_create(cenv_create(str)));	
	cenv_delete(cenv);
}

void	envs_erase(const t_envs *envs, const char *str)
{
	t_cenv		*cenv;
	t_llnode	*llnode;

	cenv = cenv_create(str);
	llnode = ft_llist_pop(envs->lst, cenv);
	if (llnode)
		ft_llnode_delete(llnode, envs->lst->content_delete);
	ft_bstree_erase(envs->bst, cenv);
	cenv_delete(cenv);
}
