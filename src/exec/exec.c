/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/23 18:05:25 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_context *ctx)
{
	print_token_list(ctx->head_token);
	// start_children(ctx);
	// ctx->exit_code = wait_children(ctx);
	// exit_process(ctx->exit_code, &d);
	// free_token_list(ctx->head_token);
	return (0);
}
