/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:53:50 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 16:34:00 by mniemaz          ###   ########.fr       */
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
 * Steps :
 *  - read line
 *  - check syntax
 *  - add to history
 *  - expand line
 *  - parse line
 *  - execute commands
 *  - reset and start over
 */
void	process_lines(t_context *ctx)
{
	while (1)
	{
		g_signal = 0;
		setup_parent_signals(ctx);
		ctx->rl_str = readline("\033[1;35m➜  pitishell$ \033[0m");
		if (g_signal == SIGINT)
			ctx->exit_code = 128 + g_signal;
		if (!ctx->rl_str)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		add_history(ctx->rl_str);
		if (!is_syntax_valid(ctx->rl_str))
		{
			ctx->exit_code = 2;
			continue ;
		}
		ctx->rl_str = expand_line(ctx->rl_str, ctx, CMD);
		if (parsing(ctx->rl_str, ctx) == EXIT_FAILURE)
			if (handle_pars_error_feedback(ctx) == EXIT_SUCCESS)
				continue ;
		ft_exec(ctx);
		reset_ctx_cmds_and_rl_str(ctx);
	}
}
