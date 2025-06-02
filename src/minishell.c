/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/02 14:27:56 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_init_exec(t_context *ctx)
{
	ctx->exec_data = malloc(sizeof(t_exec));
	if (!ctx->exec_data)
	{
		ft_fprintf(STDERR_FILENO, "clean_init_exec: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	ctx->exec_data->prev_pipe_read = -2;
	ctx->exec_data->pipe_fds[READ] = -2;
	ctx->exec_data->pipe_fds[WRITE] = -2;
	ctx->exec_data->saved_stdin = -2;
	ctx->exec_data->saved_stdout = -2;
}

void	init_ctx_cmds(t_context *ctx)
{
	ctx->head_cmd = malloc(sizeof(t_node *));
	if (!ctx->head_cmd)
	{
		ft_fprintf(STDERR_FILENO, "init_ctx_cmds: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	*(ctx->head_cmd) = NULL;
}

void	init_context(t_context *ctx)
{
	ctx->exit_code = EXIT_SUCCESS;
	ctx->hd_pid = -2;
	ctx->rl_str = NULL;
	ctx->exec_data = NULL;
	ctx->head_cmd = NULL;
	ctx->head_env = NULL;
	ctx->head_env = malloc(sizeof(t_node *));
	if (!ctx->head_env)
	{
		ft_fprintf(STDERR_FILENO, "init_context: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	(*(ctx->head_env)) = NULL;
	init_ctx_cmds(ctx);
	clean_init_exec(ctx);
}

void	minishell(char **envp)
{
	t_context	ctx;

	init_context(&ctx);
	ft_export(&ctx, envp);
	read_cmds(&ctx);
	exit_free(&ctx);
}
