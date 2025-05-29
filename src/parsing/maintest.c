/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/29 18:13:13 by mniemaz          ###   ########.fr       */
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

t_context	*read_cmds(t_context *ctx)
{
	char	*read;

	while (1)
	{
		g_signal = 0;
		setup_parent_signals(ctx);
		read = readline("pitishell$ ");
		if (g_signal == SIGINT)
			ctx->exit_code = 128 + g_signal;
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		add_history(read);
		if (is_syntax_valid(read) == EXIT_FAILURE)
			free(read);
		else
		{
			read = expand_line(read, ctx, CMD);
			if (parsing_init(read, ctx) == EXIT_FAILURE)
			{
				if (ctx->hd_pid)
				{
					if (g_signal > 0)
					{
						free_ctx_cmds(ctx);
						continue ;
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
			}
			ft_exec(ctx);
			free_ctx_cmds(ctx);
			free_exec(ctx->exec_data);
			clean_init_exec(ctx);
			free(read);
		}
	}
	free(read);
	return (NULL);
}
