/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/06 13:58:36 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_one(t_context *ctx, char *key)
{
    t_node *tmp;
    t_key_value *kv;

    if (!key)
        return ;
    tmp = *ctx->head_env;
    while(tmp)
    {
        kv = cast_to_key_value(tmp->content);
        if (ft_strncmp(key, kv->key, ft_strlen(key) + 1) == 0)
        {
            if (tmp->prev)
                tmp->prev->next = tmp->next;
            else
                *ctx->head_env = tmp->next;
            if (tmp->next)
                tmp->next->prev = tmp->prev;
            ft_lstdelone(tmp, ft_free_env_content);
            return ;
        }
        tmp = tmp->next;
    }
}

void	ft_unset(t_context *ctx, char **args)
{
    int i;

    if (!args)
        return ;
    i = 0;
    while (args[i])
    {
        ft_unset_one(ctx, args[i]);
        i++;
    }
}
