/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tabstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:33:35 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/19 15:26:01 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_tabstr(t_context *ctx)
{
	char		**res;
	t_node		*curr_node;
	t_key_value	*curr_kv;
	int			i;

	if (!ctx->head_env)
		return (NULL);
	res = malloc((ft_lstsize(*ctx->head_env) + 1) * sizeof(char *));
	if (!res)
	{
		ft_fprintf(STDERR_FILENO, "env_to_tabstr: %s\n", strerror(errno));
		exit_free(ctx);
	}
	curr_node = *ctx->head_env;
	i = 0;
	while (curr_node)
	{
		curr_kv = cast_to_key_value(curr_node->content);
		res[i] = ft_double_strjoin(ctx, curr_kv->key, "=", curr_kv->value);
		if (!res[i])
		{
			ft_fprintf(STDERR_FILENO, "env_to_tabstr: %s\n", strerror(errno));
			exit_free(ctx);
		}
		curr_node = curr_node->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
