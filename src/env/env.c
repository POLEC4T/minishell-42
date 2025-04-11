/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:34 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/11 18:31:14 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_context *ctx)
{
    t_env_node	*tmp;;

    tmp = ctx->head_env;
    while (tmp)
    {
        if (tmp->key && tmp->value)
        {
            ft_putstr_fd(tmp->key, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putstr_fd(tmp->value, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        tmp = tmp->next;
    }
}

void init_env(t_context *ctx, char **envp)
{
    
    t_env_node *curr_node;
    int i;
    char *key;
    char *value;
    char **line;
    (void) ctx;

    i = 0;
    while (envp[i])
    {
        line = ft_split(envp[i], "=");
        if (!line)
        {
            // TODO
            return ;
        }
        key = line[0];
        if (!key)
        {
            // TODO
            return ;
        }
        value = line[1];
        if (!value)
            value = ft_strdup("");
        curr_node = ft_lstnew(key, value);
        ft_lstadd_back(&(ctx->head_env), curr_node);
        i++;
    }
}



