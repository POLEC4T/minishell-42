/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 10:14:20 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_context	*read_token(t_context *ctx)
{
	char	*read;

	read = readline("pitishell$ ");
	if (read == NULL)
	{
		exit_free(ctx);
	}
	while (read)
	{
		read = quote_delimiter(read);
		read = interpretation(read, ctx);
		ctx->head_cmd = parsing(read);
		ft_exec(ctx);
		ft_free_ctx_cmds(ctx);
		free(read);
		read = readline("pitishell$ ");
	}
	free(read);
	return (NULL);
}
