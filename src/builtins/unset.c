/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 16:27:47 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_context *ctx, char *key)
{
    ctx->head_env;
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
            tmp->prev->next = tmp->next;
            ft_lstdelone(tmp, ft_free_env_content);
        }
        tmp = tmp->next;
    }
}