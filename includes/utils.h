/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:28:47 by hanelee           #+#    #+#             */
/*   Updated: 2022/01/26 17:43:30 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "tk_types.h"

t_bool	streq(const char *s1, const char *s2);
t_bool	streq_part(const char *heystack, const char *needle);
char	*ft_replace_str(char *str, \
			size_t start, size_t len, char *replace_with);
t_bool	find_last_slash(const char *path, size_t *last_slash, size_t *len);
void	move_string(char **dst, char **src);

#endif
