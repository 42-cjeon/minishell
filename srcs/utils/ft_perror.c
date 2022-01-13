/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:22:34 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/13 22:01:49 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_perror(const char *prefix)
{
	char	stmt[BUF_SIZE];
	char	*str;

	stmt[0] = '\0';
	str = strerror(errno);
	if (prefix)
	{
		ft_strlcat(stmt, prefix, BUF_SIZE);
		ft_strlcat(stmt, ": ", BUF_SIZE);
	}
	if (str)
		ft_strlcat(stmt, str, BUF_SIZE);
	ft_strlcat(stmt, "\n", BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_texit(const char *prefix, int status)
{
	ft_perror(prefix);
	exit(status);
}

void	ft_perror_custom(const char *prefix, const char *str)
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
	ft_strlcat(stmt, "\n", BUF_SIZE);
	write(STDERR_FILENO, stmt, ft_strlen(stmt));
}

void	ft_perror_custom_texit(const char *prefix,
			const char *str, int status)
{
	ft_perror_custom(prefix, str);
	exit(status);
}
