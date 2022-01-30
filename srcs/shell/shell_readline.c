/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:56:35 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/30 10:02:29 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "shell.h"

static void	handler_readline(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

static void	handler_default(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", STDERR_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

char	*shell_readline(t_shell_info *si, char *prompt)
{
	char	*ret;

	signal(SIGINT, handler_readline);
	signal(SIGQUIT, SIG_IGN);
	if (si->isterminal)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &si->readline_term_attr);
		ret = readline(prompt);
		tcsetattr(STDOUT_FILENO, TCSANOW, &si->default_term_attr);
	}
	else
		ret = readline(NULL);
	signal(SIGINT, handler_default);
	signal(SIGQUIT, handler_default);
	return (ret);
}

void	shell_add_history(const char *str)
{
	if (str && ft_isprint(str[0]))
		add_history(str);
}
