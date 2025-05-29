/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 13:01:12 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *data)
{
	if (data)
	{
		close_pipes(data);
		my_close(&data->saved_stdin);
		my_close(&data->saved_stdout);
		free(data);
	}
}

void	free_context(t_context *context)
{
	if (context->head_env != NULL)
	{
		ft_lstclear(context->head_env, ft_free_env_content);
		free(context->head_env);
	}
	free_ctx_cmds(context);
	free_exec(context->exec_data);
}
