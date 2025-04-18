/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 17:16:55 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_context *ctx, char *key)
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
            if (tmp->next)
                tmp->next->prev = tmp->prev;
            ft_lstdelone(tmp, ft_free_env_content);
            return ;
        }
        tmp = tmp->next;
    }
}