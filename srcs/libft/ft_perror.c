/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:22:34 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/17 16:03:15 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void	ft_perror(const char *prefix)
{
	char	stmt[128];
	char	*str;

	stmt[0] = '\0';
	str = strerror(errno);
	if (prefix)
	{
		ft_strlcat(stmt, prefix, 128);
		ft_strlcat(stmt, ": ", 128);
	}
	if (str)
		ft_strlcat(stmt, str, 128);
	ft_strlcat(stmt, "\n", 128);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_texit(const char *prefix, int status)
{
	ft_perror(prefix);
	exit(status);
}

void	ft_perror_custom(const char *prefix, const char *str)
{
	char	stmt[128];

	stmt[0] = '\0';
	if (prefix)
	{
		ft_strlcat(stmt, prefix, 128);
		ft_strlcat(stmt, ": ", 128);
	}
	if (str)
		ft_strlcat(stmt, str, 128);
	ft_strlcat(stmt, "\n", 128);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_custom_texit(const char *prefix,
			const char *str, int status)
{
	ft_perror_custom(prefix, str);
	exit(status);
}
