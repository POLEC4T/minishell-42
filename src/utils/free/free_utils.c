/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/02 10:20:31 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_content(void *content)
{
	t_key_value	*kv;

	if (!content)
		return ;
	kv = cast_to_key_value(content);
	free(kv->key);
	free(kv->value);
	free(kv);
}

void	close_exec_fds(t_exec *data)
{
	close_pipes(data);
	my_close(&data->saved_stdin);
	my_close(&data->saved_stdout);
}

void	free_exec(t_exec *data)
{
	if (data)
	{
		close_exec_fds(data);
		free(data);
	}
}

void	free_context(t_context *ctx)
{
	if (ctx->head_env != NULL)
	{
		ft_lstclear(ctx->head_env, ft_free_env_content);
		free(ctx->head_env);
	}
	free_ctx_cmds(ctx);
	free_exec(ctx->exec_data);
	if (ctx->rl_str != NULL)
		free(ctx->rl_str);
}
