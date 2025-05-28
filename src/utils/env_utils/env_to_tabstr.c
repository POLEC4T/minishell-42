/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tabstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:33:35 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/28 20:54:47 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_env_to_tabstr(t_context *ctx, char **res, char *to_free)
{
	ft_fprintf(STDERR_FILENO, "env_to_tabstr: %s\n", strerror(errno));
	if (res)
		ft_free_tab((void **)res);
	free(to_free);
	exit_free(ctx);
}

char	**env_to_tabstr(t_context *ctx, char *to_free)
{
	char		**res;
	t_node		*curr_node;
	t_key_value	*curr_kv;
	int			i;

	if (!ctx->head_env)
		return (NULL);
	res = ft_calloc((ft_lstsize(*ctx->head_env) + 1), sizeof(char *));
	if (!res)
		err_env_to_tabstr(ctx, res, to_free);
	curr_node = *ctx->head_env;
	i = 0;
	while (curr_node)
	{
		curr_kv = cast_to_key_value(curr_node->content);
		res[i] = ft_double_strjoin(ctx, curr_kv->key, "=", curr_kv->value);
		if (!res[i++])
			err_env_to_tabstr(ctx, res, to_free);
		curr_node = curr_node->next;
	}
	return (res);
}
