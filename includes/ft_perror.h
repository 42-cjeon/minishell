/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:22:44 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/09 20:58:07 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERROR_H
# define PERROR_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define BUF_SIZE	128

void	ft_perror_errno(const char *prefix_1, const char *prefix_2);
void	ft_perror_errno_texit(const char *prefix_1,
			const char *prefix_2, int status);

void	ft_perror_custom(const char *prefix,
			const char *suffix, const char *str);
void	ft_perror_custom_texit(const char *prefix,
			const char *suffix, const char *str, int status);

#endif
