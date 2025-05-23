/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/21 15:12:43 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_code = 0;

void	parent_sigint_handler(int sigint)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 128 + sigint;
}

t_context	*read_token(t_context *ctx)
{
	char	*read;

	while (1)
	{
		// todo : secure signal
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		read = readline("pitishell$ ");
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		if (syntax(read) != -1)
		{
			add_history(read);
			read = interpretation(read, ctx);
			ctx->head_cmd = parsing_init(read, ctx);
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
