/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cenv_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:03:49 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 17:07:10 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "cenv.h"
#include "libft.h"

void	cenv_print(t_cenv *cenv)
{
	if (cenv)
	{
		if (cenv->key && cenv->value)
		{
			write(STDOUT_FILENO, cenv->key, ft_strlen(cenv->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, cenv->value, ft_strlen(cenv->value));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

void	cenv_print_export(t_cenv *cenv)
{
	if (cenv)
	{
		if (cenv->key)
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, cenv->key, ft_strlen(cenv->key));
		}
		if (cenv->value)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, cenv->value, ft_strlen(cenv->value));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}
