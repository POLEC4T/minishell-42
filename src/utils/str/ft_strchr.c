/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:56:48 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/23 17:04:21 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *string, int c)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)c)
			break ;
		i++;
	}
	if (string[i] == (char)c)
		return ((char *)string + i);
	return (0);
}
