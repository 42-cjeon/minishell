/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:22:34 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/09 20:56:18 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_perror.h"

void	ft_perror_errno(const char *prefix_1, const char *prefix_2)
{
	char	stmt[BUF_SIZE];
	char	*str;

	stmt[0] = '\0';
	str = strerror(errno);
	if (prefix_1)
	{
		ft_strlcat(stmt, prefix_1, BUF_SIZE);
		ft_strlcat(stmt, ": ", BUF_SIZE);
	}
	if (prefix_2)
	{
		ft_strlcat(stmt, prefix_2, BUF_SIZE);
		ft_strlcat(stmt, ": ", BUF_SIZE);
	}
	if (str)
		ft_strlcat(stmt, str, BUF_SIZE);
	ft_strlcat(stmt, "\n", BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_errno_texit(const char *prefix_1,
			const char *prefix_2, int status)
{
	ft_perror_errno(prefix_1, prefix_2);
	exit(status);
}

void	ft_perror_custom(const char *prefix,
			const char *suffix, const char *str)
{
	char	stmt[BUF_SIZE];

	stmt[0] = '\0';
	if (prefix)
	{
		ft_strlcat(stmt, prefix, BUF_SIZE);
		ft_strlcat(stmt, ": ", BUF_SIZE);
	}
	if (str)
		ft_strlcat(stmt, str, BUF_SIZE);
	if (suffix)
	{
		ft_strlcat(stmt, ": ", BUF_SIZE);
		ft_strlcat(stmt, suffix, BUF_SIZE);
	}
	ft_strlcat(stmt, "\n", BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_custom_texit(const char *prefix,
			const char *suffix, const char *str, int status)
{
	ft_perror_custom(prefix, suffix, str);
	exit(status);
}
