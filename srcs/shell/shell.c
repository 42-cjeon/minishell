/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:03 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 12:26:28 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

static void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	shell_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	signal(SIGALRM, handler);
	signal(SIGTSTP, handler);
	signal(SIGTTIN, handler);
	signal(SIGTTOU, handler);
}

void	shell_print_banner(void)
{
	ft_putstr_fd("｀、、｀ヽ｀ヽ｀、、ヽヽ、｀、ヽ｀ヽ｀ヽヽ｀\n", STDOUT_FILENO);
	ft_putstr_fd("ヽ｀、｀ヽ｀、ヽ｀｀、ヽ｀ヽ｀、ヽヽ｀ヽ、ヽ\n", STDOUT_FILENO);
	ft_putstr_fd("｀ヽ、ヽヽ｀ヽ｀、｀｀ヽ｀ヽ、ヽ、ヽ｀ヽ｀ヽ\n", STDOUT_FILENO);
	ft_putstr_fd("、ヽ｀ヽ｀、ヽヽ｀｀、ヽ｀𐂊 𐂊 、ヽ｀ヽヽ｀\n", STDOUT_FILENO);
	ft_putstr_fd("｀ヽ｀、、[minishell] by cjeon, hanelee｀ヽ｀\n", STDOUT_FILENO);
}

char	*shell_readline(void)
{
	char	*ret;

	ret = readline("minishell$ ");
	return (ret);
}

void	shell_add_history(const char *str)
{
	if (str && ft_isprint(str[0]))
		add_history(str);
}
