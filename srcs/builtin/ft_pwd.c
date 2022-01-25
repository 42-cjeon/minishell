/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:50:11 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/25 20:47:15 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_pwd(char **cmd)
{
	char	*path;

	if (!cmd)
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
		ft_perror_texit(PROJECT_NAME, 1);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
