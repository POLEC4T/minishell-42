/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:34 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 15:57:34 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(t_context *ctx, char **envp)
{
    
    t_node *curr_node;
    int i;
    char **line;
    // char *key;
    char *value;

    i = -1;
    while (envp && envp[++i])
    {
        line = ft_split_first(envp[i], "=");
        if (!line)
        {
            // TODO
            
            continue ;
        }
        if (!line[0])
        {
            continue;
        }
        if (!line[1])
            value = NULL;
        else
            value = line[1];
        curr_node = ft_envnew(line[0], value);
        if (!curr_node)
        {
            continue;
        }
        ft_lstadd_back(ctx->head_env, curr_node);
        ft_free_tab((void **)line);
    }
}



