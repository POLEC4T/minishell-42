/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief redirects the standard input and output to the given ones
 */
void	redirect(int input, int output, t_context *ctx)
{
	if (input >= 0 && dup2(input, STDIN_FILENO) == -1)
		exit_free(ctx);
	if (output >= 0 && dup2(output, STDOUT_FILENO) == -1)
		exit_free(ctx);
}

void	secure_fork(int *pid, t_context *ctx)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_dprintf(STDERR_FILENO, "fork: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
}

void	secure_pipe(t_context *ctx)
{
	int	pipe_ret;

	pipe_ret = pipe(ctx->exec_data->pipe_fds);
	if (pipe_ret == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipe: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
}
