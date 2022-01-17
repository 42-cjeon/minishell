/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:13 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/17 15:38:27 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

void	shell_init(void);
void	shell_print_banner(void);
char	*shell_readline(void);
void	shell_add_history(const char *str);

#endif
