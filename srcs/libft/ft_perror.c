/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:22:34 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/16 17:41:31 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"

void	ft_perror(const char *prefix)
{
	char	stmt[PERROR_BUF_SIZE];
	char	*str;

	stmt[0] = '\0';
	str = strerror(errno);
	if (prefix)
	{
		ft_strlcat(stmt, prefix, PERROR_BUF_SIZE);
		ft_strlcat(stmt, ": ", PERROR_BUF_SIZE);
	}
	if (str)
		ft_strlcat(stmt, str, PERROR_BUF_SIZE);
	ft_strlcat(stmt, "\n", PERROR_BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_texit(const char *prefix, int status)
{
	ft_perror(prefix);
	exit(status);
}

void	ft_perror_custom(const char *prefix, const char *str)
{
	char	stmt[PERROR_BUF_SIZE];

	stmt[0] = '\0';
	if (prefix)
	{
		ft_strlcat(stmt, prefix, PERROR_BUF_SIZE);
		ft_strlcat(stmt, ": ", PERROR_BUF_SIZE);
	}
	if (str)
		ft_strlcat(stmt, str, PERROR_BUF_SIZE);
	ft_strlcat(stmt, "\n", PERROR_BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_custom_texit(const char *prefix,
			const char *str, int status)
{
	ft_perror_custom(prefix, str);
	exit(status);
}
