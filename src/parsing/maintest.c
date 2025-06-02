/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/02 13:47:05 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

void	setup_parent_signals(t_context *ctx)
{
	if (signal(SIGINT, parent_sigint_handler) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "setup_parent_signals: %s\n",
			strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "setup_parent_signals: %s\n",
			strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
}

/**
 * if we are in the parent
 * 	if a signal occured -> we skip to the next readline
 * 	else -> it means an error occured (such as alloc error), then we exit
 * else if we are in a child
 * 	if a signal occured and no error occured, we set the exit_code to the
 *  signal, so the parent knows the child has been exited with a signal
 * 	WHAT IS NOT WRITTEN : if an error occured (still in the child), the
 * 	exit_code is already set
 */
int	handle_error_feedback(t_context *ctx)
{
	if (ctx->hd_pid)
	{
		if (g_signal > 0)
		{
			free_ctx_cmds(ctx);
			init_ctx_cmds(ctx);
			free(ctx->rl_str);
			ctx->rl_str = NULL;
			return (EXIT_SUCCESS);
		}
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	else if (ctx->hd_pid == 0)
	{
		if (g_signal > 0 && ctx->exit_code == EXIT_SUCCESS)
			ctx->exit_code = 128 + g_signal;
		exit_free(ctx);
	}
	return (EXIT_FAILURE);
}

t_context	*read_cmds(t_context *ctx)
{
	while (1)
	{
		g_signal = 0;
		setup_parent_signals(ctx);
		ctx->rl_str = readline("pitishell$ ");
		if (g_signal == SIGINT)
			ctx->exit_code = 128 + g_signal;
		if (!ctx->rl_str)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		add_history(ctx->rl_str);
		if (!is_syntax_valid(ctx->rl_str))
			continue ;
		ctx->rl_str = expand_line(ctx->rl_str, ctx, CMD);
		if (parsing(ctx->rl_str, ctx) == EXIT_FAILURE)
			if (handle_error_feedback(ctx) == EXIT_SUCCESS)
				continue ;
		ft_exec(ctx);
		free_ctx_cmds(ctx);
		init_ctx_cmds(ctx);
		free(ctx->rl_str);
		ctx->rl_str = NULL;
		free_exec(ctx->exec_data);
		clean_init_exec(ctx);
	}
	return (NULL);
}
