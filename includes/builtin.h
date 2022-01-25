/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:01:06 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 04:13:33 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(const char *const *cmd);
int		ft_echo(const char *const *cmd);
int		ft_env(const char *const *cmd);
int		ft_exit(const char *const *cmd);
int		ft_export(const char *const *cmd);
int		ft_pwd(const char *const *cmd);
int		ft_unset(const char *const *cmd);

#endif
