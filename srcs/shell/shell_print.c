/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:54 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 17:58:37 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

void	shell_print_banner(void)
{
	ft_putstr_fd("｀、、｀ヽ｀ヽ｀、、ヽヽ、｀、ヽ｀ヽ｀ヽヽ｀\n", STDOUT_FILENO);
	ft_putstr_fd("ヽ｀、｀ヽ｀、ヽ｀｀、ヽ｀ヽ｀、ヽヽ｀ヽ、ヽ\n", STDOUT_FILENO);
	ft_putstr_fd("｀ヽ、ヽヽ｀ヽ｀、｀｀ヽ｀ヽ、ヽ、ヽ｀ヽ｀ヽ\n", STDOUT_FILENO);
	ft_putstr_fd("、ヽ｀ヽ｀、ヽヽ｀｀、ヽ｀𐂊 𐂊 、ヽ｀ヽヽ｀\n", STDOUT_FILENO);
	ft_putstr_fd("｀ヽ｀、、[minishell] by cjeon, hanelee｀ヽ｀\n", STDOUT_FILENO);
}
