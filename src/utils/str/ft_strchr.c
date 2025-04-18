/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:56:48 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/18 14:18:15 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)searchedChar)
			break ;
		i++;
	}
	if (string[i] == (char)searchedChar)
		return ((char *)string + i);
	return (0);
}
