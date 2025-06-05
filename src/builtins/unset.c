/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 16:32:09 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_one(t_context *ctx, char *key)
{
	t_node		*curr_node;
	t_key_value	*kv;

	if (!key)
		return ;
	curr_node = *ctx->head_env;
	while (curr_node)
	{
		kv = cast_to_key_value(curr_node->content);
		if (ft_strncmp(key, kv->key, ft_strlen(key) + 1) == 0)
		{
			if (curr_node->prev)
				curr_node->prev->next = curr_node->next;
			else
				*ctx->head_env = curr_node->next;
			if (curr_node->next)
				curr_node->next->prev = curr_node->prev;
			ft_lstdelone(curr_node, ft_free_env_content);
			return ;
		}
		curr_node = curr_node->next;
	}
}

int	ft_unset(t_context *ctx, char **args)
{
	int	i;

	if (!args)
		return (EXIT_SUCCESS);
	i = 0;
	while (args[i])
	{
		ft_unset_one(ctx, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
