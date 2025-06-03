/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:15:56 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 14:36:54 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen((char *)src);
	if (size == 0)
		return (srclen);
	i = -1;
	while (src[++i] && i + 1 < size)
		dst[i] = src[i];
	dst[i] = '\0';
	return (srclen);
}
