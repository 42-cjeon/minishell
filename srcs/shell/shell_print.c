/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:54 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/30 12:44:12 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

void	shell_print_banner(void)
{
	ft_putstr_fd("｀、、｀ヽ｀ヽ｀、、ヽヽ、｀、ヽ｀ヽ｀ヽヽ｀\n", STDERR_FILENO);
	ft_putstr_fd("ヽ｀、｀ヽ｀、ヽ｀｀、ヽ｀ヽ｀、ヽヽ｀ヽ、ヽ\n", STDERR_FILENO);
	ft_putstr_fd("｀ヽ、ヽヽ｀ヽ｀、｀｀ヽ｀ヽ、ヽ、ヽ｀ヽ｀ヽ\n", STDERR_FILENO);
	ft_putstr_fd("、ヽ｀ヽ｀、ヽヽ｀｀、ヽ｀𐂊 𐂊 、ヽ｀ヽヽ｀\n", STDERR_FILENO);
	ft_putstr_fd("｀ヽ｀、、[minishell] by cjeon, hanelee｀ヽ｀\n", STDERR_FILENO);
}
