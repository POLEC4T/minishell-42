/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/02 16:37:03 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_context *ctx)
{
	t_cmd	*cmd;

	if (ctx->head_cmd == NULL || *ctx->head_cmd == NULL)
		return ;
	cmd = cast_to_cmd((*ctx->head_cmd)->content);
	start_children(ctx);
	wait_children(ctx);
}
