/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/18 16:35:35 by mniemaz          ###   ########.fr       */
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
    init_context(&ctx);
    init_env(&ctx, envp);
    // t_key_value **args;

    // args = malloc(sizeof(t_key_value*) * 3);
    // args[0] = malloc(sizeof(t_key_value));
    // args[1] = malloc(sizeof(t_key_value));

    // args[0]->key = "key1";
    // args[0]->value = "value1";
    // args[1]->key = "key2";
    // args[1]->value = "value2";
    // args[2] = NULL;
    // ft_export(&ctx, args);
    // ft_env(ctx.head_env);


    print_env_val(ctx.head_env, "PWD");
    print_env_val(ctx.head_env, "OLDPWD");

    cd(&ctx, (char *[]){ "cd", "~/travail/fd", NULL });


    print_env_val(ctx.head_env, "PWD");
    print_env_val(ctx.head_env, "OLDPWD");
    
    ft_lstclear(ctx.head_env, ft_free_env_content);
    if (ctx.head_env)
        free(ctx.head_env);
    // ft_free_tab((void **)args);
}