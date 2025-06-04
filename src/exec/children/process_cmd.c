/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 18:29:29 by mniemaz          ###   ########.fr       */
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
	t_cmd *cmd;

	cmd = cast_to_cmd(node_cmd->content);
	if (cmd->args[0] == NULL)
		exit_free(ctx);
	setup_child_signals(ctx);
	if (open_cmd_redirs(node_cmd) == EXIT_FAILURE)
	{
		ctx->exit_code = EXIT_FAILURE;
		if (cmd->pid == CHILD)
			exit_free(ctx);
		return ;
	}
	dup_cmd_redirs(ctx, node_cmd);
	close_pipes(ctx->exec_data);
	close_all_cmds_redirs(ctx->head_cmd);
	exec_cmd(ctx, node_cmd);
}
