/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:53:50 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:26:06 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

static void	reset_ctx_cmds_and_rl_str(t_context *ctx)
{
	free_ctx_cmds(ctx);
	init_ctx_cmds(ctx);
	free(ctx->rl_str);
	ctx->rl_str = NULL;
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
static int	handle_pars_error_feedback(t_context *ctx)
{
	if (ctx->hd_pid)
	{
		if (g_signal > 0)
		{
			reset_ctx_cmds_and_rl_str(ctx);
			return (EXIT_SUCCESS);
		}
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	else if (ctx->hd_pid == CHILD)
	{
		if (g_signal > 0 && ctx->exit_code == EXIT_SUCCESS)
			ctx->exit_code = 128 + g_signal;
		exit_free(ctx);
	}
	return (EXIT_FAILURE);
}

/**
 * rl_catch_signals (a readline global variable) is set to 0 to cancel 
 * readline's signal handling.
 * otherwise, CTRL-C would be caught by readline and cause it to leak memory.
 * How to reproduce the leak:
 * - remove the line rl_catch_signals = 0
 * - compile the program
 * - resize the terminal to be small vertically
 * - type /dev/
 * - press tab
 * - press y to confirm the completion
 * - CTRL-C
 * - try to type something
 * -> causing readline to leak
 */
void	process_lines(t_context *ctx)
{
	rl_catch_signals = 0;
	while (1)
	{
		g_signal = 0;
		setup_parent_signals(ctx);
		ctx->rl_str = readline("➜  pitishell$ ");
		if (g_signal == SIGINT)
			ctx->exit_code = 128 + g_signal;
		if (!ctx->rl_str)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		if (ctx->rl_str[0] != '\0')
			add_history(ctx->rl_str);
		if (!is_syntax_valid(ctx, ctx->rl_str))
			continue ;
		ctx->rl_str = expand_line(ctx->rl_str, ctx, CMD);
		if (parsing(ctx->rl_str, ctx) == EXIT_FAILURE)
			if (handle_pars_error_feedback(ctx) == EXIT_SUCCESS)
				continue ;
		ft_exec(ctx);
		reset_ctx_cmds_and_rl_str(ctx);
	}
}
