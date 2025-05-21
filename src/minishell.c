/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/21 10:54:17 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_init_exec(t_context *ctx)
{
	ctx->exec_data = malloc(sizeof(t_exec));
	if (!ctx->exec_data)
	{
		ft_fprintf(STDERR_FILENO, "clean_init_exec: %s\n", strerror(errno));
		exit_free(ctx);
	}
	ctx->exec_data->prev_pipe_read = -2;
	ctx->exec_data->pipe_fds[READ] = -2;
	ctx->exec_data->pipe_fds[WRITE] = -2;
	ctx->exec_data->saved_stdin = -2;
	ctx->exec_data->saved_stdout = -2;
}

void	init_context(t_context *context)
{
	context->head_env = malloc(sizeof(t_node *));
	if (!context->head_env)
		exit(EXIT_FAILURE);
	(*(context->head_env)) = NULL;
	context->head_cmd = NULL;
	context->exit_code = 0;
	clean_init_exec(context);
}

void	minishell(char **envp)
{
	t_context	ctx;

	init_context(&ctx);
	ft_export(&ctx, envp);
	read_token(&ctx);
	exit_free(&ctx);
}
