/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/19 17:44:45 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			varg = 0;

volatile sig_atomic_t g_readline_active = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	varg = 1;
	if (g_readline_active)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}

t_context	*read_token(t_context *ctx)
{
	char	*read;

	while (1)
	{
		varg = 0;
		if (signal(SIGINT, handle_sigint) == SIG_ERR)
		{
			perror("Erreur lors de la configuration du signal");
			exit(42);
		}
		// todo : secure signal
		signal(SIGQUIT, SIG_IGN);
		g_readline_active = 1;
		read = readline("pitishell$ ");
		g_readline_active = 0;
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		// if (varg != 0)
		// { // Si SIGINT a été reçu
		// 	varg = 0;
		// 	add_history(read);
		// 	free(read);
		// 	printf("skip\n");
		// 	continue ;
		// }
		add_history(read);
		read = quote_delimiter(read);
		read = interpretation(read, ctx);
		ctx->head_cmd = parsing_init(read, ctx);
		ft_exec(ctx);
		ft_free_ctx_cmds(ctx);
		free_exec(ctx->exec_data);
		clean_init_exec(ctx);
		free(read);
	}
	free(read);
	return (NULL);
}
