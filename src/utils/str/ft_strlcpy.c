/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:15:56 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/14 14:51:08 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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
