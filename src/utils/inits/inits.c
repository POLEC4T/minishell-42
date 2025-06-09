/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:25:18 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_init_exec(t_context *ctx)
{
	ctx->exec_data = malloc(sizeof(t_exec));
	if (!ctx->exec_data)
	{
		ft_dprintf(STDERR_FILENO, "clean_init_exec: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	ctx->exec_data->prev_pipe_read = UNDEFINED_INT;
	ctx->exec_data->pipe_fds[READ] = UNDEFINED_INT;
	ctx->exec_data->pipe_fds[WRITE] = UNDEFINED_INT;
	ctx->exec_data->saved_stdin = UNDEFINED_INT;
	ctx->exec_data->saved_stdout = UNDEFINED_INT;
}

void	init_ctx_cmds(t_context *ctx)
{
	ctx->head_cmd = malloc(sizeof(t_node *));
	if (!ctx->head_cmd)
	{
		ft_dprintf(STDERR_FILENO, "init_ctx_cmds: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	*(ctx->head_cmd) = NULL;
}

void	init_context(t_context *ctx)
{
	ctx->exit_code = EXIT_SUCCESS;
	ctx->hd_pid = UNDEFINED_INT;
	ctx->rl_str = NULL;
	ctx->exec_data = NULL;
	ctx->head_cmd = NULL;
	ctx->head_env = NULL;
	ctx->head_env = malloc(sizeof(t_node *));
	if (!ctx->head_env)
	{
		ft_dprintf(STDERR_FILENO, "init_context: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	(*(ctx->head_env)) = NULL;
	init_ctx_cmds(ctx);
	clean_init_exec(ctx);
}
