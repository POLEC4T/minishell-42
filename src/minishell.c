/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/22 17:38:26 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_context(t_context *context)
{
    context->head_env = malloc(sizeof(t_node *));
    if (!context->head_env)
        exit(EXIT_FAILURE);
    (*(context->head_env)) = NULL;
}

void minishell(char **envp)
{
    t_context ctx;
    (void) envp;
    init_context(&ctx);
    ft_export(&ctx, envp);
    ft_pwd((char *[]){NULL});

    ft_lstclear(ctx.head_env, ft_free_env_content);
    if (ctx.head_env)
        free(ctx.head_env);
    // ft_free_tab((void **)args);
}