/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:59:33 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/28 10:20:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envs.h"
#include "libft.h"
#include "shell.h"
#include "tk_types.h"
#include "utils.h"

size_t	get_varname_len(char *str)
{
	size_t	len;

	len = 0;
	if (*str == '?')
		return (1);
	while (str[len] != '\0' && tk_isidentifier(str[len]))
		len++;
	return (len);
}

char	*get_var_from_env(t_envs *envs, char *str, size_t start, size_t len)
{
	char	*varname;
	char	*env;

	varname = ft_substr(str, start, len);
	env = envs_get_value(envs, varname);
	free(varname);
	if (env == NULL)
		return (ft_strdup(""));
	return (ft_strdup(env));
}

size_t	replace_variable(t_shell_info *si, char **str, const size_t start)
{
	size_t	len;
	char	*var;
	char	*newstr;

	len = get_varname_len(*str + start + 1);
	if (len == 0)
		return (1);
	else if (len == 1 && (*str)[start + len] == '?')
		var = ft_itoa(si->last_status);
	else
		var = get_var_from_env(si->envs, *str, start + 1, len);
	newstr = ft_replace_str(*str, start, len + 1, var);
	len = ft_strlen(var);
	free(var);
	free(*str);
	*str = newstr;
	return (len);
}