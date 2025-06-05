/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:39:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:31:41 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_double_strjoin(t_context *ctx, char *s1, char *s2, char *s3)
{
	char	*res;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s3 == NULL)
	{
		res = ft_strjoin(s1, s2);
		if (!res)
		{
			ft_fprintf(STDERR_FILENO, "double_strjoin: %s\n", strerror(errno));
			exit_free(ctx);
		}
		return (res);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(res + ft_strlen(s1), s2, ft_strlen(s2));
	ft_memcpy(res + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3));
	res[len] = '\0';
	return (res);
}
