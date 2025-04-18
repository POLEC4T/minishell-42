/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:32:18 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/18 16:32:33 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_in_str(char c, char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (c == str[i])
			return (1);
	return (0);
}