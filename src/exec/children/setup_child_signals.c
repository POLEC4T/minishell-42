/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:37:56 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 19:44:41 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_signals(t_context *ctx)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "start_children: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "start_children: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
}
