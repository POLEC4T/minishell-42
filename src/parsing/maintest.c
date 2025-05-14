/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/14 10:01:27 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_context	*read_token(t_context *ctx)
{
	char	*read;

	read = readline("pitishell$ ");
	if (read == NULL)
	{
		write(1, "exit\n", 6);
		exit_free(ctx);
	}
	while (read)
	{
		add_history(read);
		read = quote_delimiter(read);
		read = interpretation(read, ctx);
		ctx->head_cmd = parsing_init(read);
		ft_exec(ctx);
		ft_free_ctx_cmds(ctx);
		free_exec(ctx->exec_data);
		clean_init_exec(ctx);
		free(read);
		read = readline("pitishell$ ");
		if (!read)
		{
			write(1, "exit\n", 6);
			exit_free(ctx);
		}
	}
	free(read);
	return (NULL);
}
