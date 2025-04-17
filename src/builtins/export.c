/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:09:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/16 17:55:33 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_key_valid(char *key)
{
	int	i;

	if (!key || ft_isdigit(key[0]))
		return (0);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_context *ctx, t_key_value **args)
{
	t_node	*new_node;
	int			i;

	i = -1;
	while (args[++i])
	{
		if (!ft_is_key_valid(args[i]->key))
		{
			ft_fprintf(STDERR_FILENO,
				"export: `%s=%s': not a valid identifier\n", args[i]->key,
				args[i]->value);
			continue ;
		}
		new_node = ft_get_env(ctx->head_env, args[i]->key);
		if (!new_node)
		{
			new_node = ft_envnew(args[i]->key, args[i]->value);
			ft_lstadd_back(ctx->head_env, new_node);
		}
		else
		{
			ft_edit_env_val(ctx->head_env, args[i]->key, args[i]->value);
		}
	}
}
