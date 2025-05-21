/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/19 10:40:06 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief this function processes
 * - the child (created the calling function in a fork)
 * - OR
 * - one builtin command in the parent process
 * @example
 * pitishell$ echo hello -> in the parent process
 * pitishell$ echo hello | grep hello -> all in children processes
 * pitishell$ cat file.txt -> in a child process
 */
void	process_cmd(t_context *ctx, t_node *node_cmd)
{
	if (cast_to_cmd(node_cmd->content)->args[0] == NULL)
		exit_free(ctx);
	dup_cmd_redirs(ctx, node_cmd);
	close_pipes(ctx->exec_data);
	close_all_cmds_redirs(ctx->head_cmd);
	exec_cmd(ctx, node_cmd);
}
