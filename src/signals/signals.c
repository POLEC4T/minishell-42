/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:12:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 15:54:56 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_sigint_handler(int sigint)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = sigint;
}

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

static void	hd_sigint_handler(int sig)
{
	g_signal = sig;
}

/**
 * using sigaction to allow gnl to be interrupted by a signal,
 * thanks to the sa_flags = 0
 */
int	setup_hd_signals(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = hd_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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