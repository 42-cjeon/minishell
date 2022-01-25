/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cenv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:51:45 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 14:04:17 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cenv.h"
#include "libft.h"
#include <stdlib.h>

static char	*key_create(const char *str, const char *eq_pos)
{
	char	*ret;
	int		size;

	if (eq_pos)
	{
		size = eq_pos - str;
		if (size < 0)
			size *= -1;
		ret = (char *)ft_malloc((size + 1) * sizeof(char));
		ft_strlcpy(ret, str, size + 1);
	}
	else
		ret = ft_strdup(str);
	return (ret);
}

t_cenv	*cenv_create(const char *str)
{
	t_cenv	*ret;
	char	*eq_pos;

	eq_pos = ft_strchr(str, '=');
	ret = (t_cenv *)ft_malloc(sizeof(t_cenv));
	ret->key = key_create(str, eq_pos);
	ret->value = NULL;
	if (eq_pos)
		ret->value = ft_strdup(eq_pos + 1);
	return (ret);
}

void	cenv_delete(t_cenv *cenv)
{
	if (cenv)
	{
		if (cenv->key)
			free(cenv->key);
		if (cenv->value)
			free(cenv->value);
		free(cenv);
	}
}

int	cenv_compare(const t_cenv *cenv1, const t_cenv *cenv2)
{
	return (ft_strcmp(cenv1->key, cenv2->key));
}
