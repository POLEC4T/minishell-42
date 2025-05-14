/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:02:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/14 14:50:45 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief returns the index of the first occurrence of c in s
 * @details if c is not found, returns -1
 */
int	ft_strchr_idx(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (*(unsigned char *)(s + i) == (char)c)
			return (i);
	return (-1);
}
