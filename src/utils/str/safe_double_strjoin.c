/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_double_strjoin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:42:55 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_ft_double_strjoin(t_context *ctx, char *s1, char *s2, char *s3)
{
	char	*res;

	res = ft_double_strjoin(ctx, s1, s2, s3);
	if (!res)
	{
		ft_dprintf(STDERR_FILENO, "safe_ft_strjoin: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	return (res);
}
