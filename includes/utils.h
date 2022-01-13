/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:28:47 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/13 22:04:54 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define BUF_SIZE	128

void	*ft_malloc(size_t size);

void	ft_perror(const char *prefix);
void	ft_perror_texit(const char *prefix, int status);
void	ft_perror_custom(const char *prefix, const char *str);
void	ft_perror_custom_texit(const char *prefix, const char *str, int status);

#endif
