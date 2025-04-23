/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/23 16:36:38 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_context(t_context *context)
{
	context->head_env = malloc(sizeof(t_node *));
	if (!context->head_env)
		exit(EXIT_FAILURE);
	(*(context->head_env)) = NULL;
	context->exit_code = 0;
}

void	minishell(char **envp)
{
	t_context ctx;
	init_context(&ctx);
	ft_export(&ctx, envp);
	//ft_exit(&ctx, (char *[2]){"-9223372036854775809", NULL});
	ctx.head_token = read_token();
	exit_free(&ctx);
	// ft_free_tab((void **)args);
}