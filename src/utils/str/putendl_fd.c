/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:10:12 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/14 14:52:11 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putendl_fd(char *s, int fd)
{
	int counter;

	counter = 0;
	if (!s)
		return (-2);
	counter += write(fd, s, ft_strlen(s));
	counter += write(fd, "\n", 1);
	if (counter < 0)
		return (-1);
	return (counter);
}