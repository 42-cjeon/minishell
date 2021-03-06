/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanelee <hanelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:41:58 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/26 17:23:06 by hanelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*str;
	char			*ps;

	len = (unsigned int)ft_strlen(s);
	if (f == NULL)
		return (ft_strdup(s));
	str = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	ps = (char *)s;
	while (len--)
		*str++ = f(i++, *ps++);
	*str = '\0';
	return (str - i);
}
