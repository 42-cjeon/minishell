/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:01:06 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 18:15:35 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "envs.h"

int		ft_cd(char **cmd);
int		ft_echo(char **cmd);
int		ft_exit(char **cmd);
int		ft_pwd(char **cmd);
int		ft_env(char **cmd, const t_envs *envs);
int		ft_export(char **cmd, const t_envs *envs);
int		ft_unset(char **cmd, const t_envs *envs);

#endif
