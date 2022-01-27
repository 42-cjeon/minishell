/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:18:10 by cjeon             #+#    #+#             */
/*   Updated: 2022/01/27 14:39:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wifexited(int status)
{
	return ((status & 0177) == 0);
}

int	ft_wifsignaled(int status)
{
	return ((status & 0177) != 0);
}

int	ft_wexitstatus(int status)
{
	return (((status >> 8) & 0x000000ff) % 128);
}

int	ft_wtermsig(int status)
{
	return ((status & 0177) + 128);
}
