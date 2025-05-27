/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/27 14:34:05 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

void	parent_sigint_handler(int sigint)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = sigint;
}

t_context	*read_token(t_context *ctx)
{
	char	*read;

	while (1)
	{
		g_signal = 0;
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		read = readline("pitishell$ ");
		if (g_signal == SIGINT)
			ctx->exit_code = 128 + g_signal;
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		if (syntax(read) != -1)
		{
			add_history(read);
			read = interpretation(read, ctx, CMD);
			if (parsing_init(read, ctx) == EXIT_FAILURE)
			{
				if (ctx->hd_pid)
				{
					if (g_signal > 0)
					{
						ft_free_ctx_cmds(ctx);
						continue ;
					}
					exit_free(ctx);
				}
				else if (ctx->hd_pid == 0)
				{
					// todo, handle: g_signal == 0 peut vouloir dire que eof
					// a marche mais aussi qu'une erreur est survenue (malloc..)
					if (g_signal == 0)
						ctx->exit_code = EXIT_SUCCESS;
					else
						ctx->exit_code = 128 + g_signal;
					exit_free(ctx);
				}
			}
			ft_exec(ctx);
			ft_free_ctx_cmds(ctx);
			free_exec(ctx->exec_data);
			clean_init_exec(ctx);
			free(read);
		}
		else
		{
			clean_init_exec(ctx);
			free(read);
		}
	}
	free(read);
	return (NULL);
}
