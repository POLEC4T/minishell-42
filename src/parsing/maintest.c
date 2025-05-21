/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/21 11:16:40 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			varg = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	varg = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

t_context	*read_token(t_context *ctx)
{
	char	*read;

	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("Erreur lors de la configuration du signal");
		exit(42);
	}
	while (1)
	{
		varg = 0;
		read = readline("pitishell$ ");
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
		if (varg != 0)
		{ // Si SIGINT a été reçu
			varg = 0;
			add_history(read);
			free(read);
			continue ;
		}
		else
		{
			if(syntax(read) != -1)
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
	}
	free(read);
	return (NULL);
}
