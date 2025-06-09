/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief processes the command, but not always the same way
 * @details if the command is a builtin and there is no other commands,
 * it will be executed in the parent process. Else, it will be executed
 * in a child process
 */
static void	process_cmd_if(t_context *ctx, t_node *cmd_node)
{
	t_cmd	*cmd;
	int		is_cmd_a_single_builtin;

	cmd = cast_to_cmd(cmd_node->content);
	is_cmd_a_single_builtin = !cmd_node->next && !cmd_node->prev
		&& is_builtin_cmd(cmd->args[0]);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		ft_dprintf(STDERR_FILENO, "process_cmd_if: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	if (is_cmd_a_single_builtin)
		process_cmd(ctx, cmd);
	else
	{
		secure_fork(&cmd->pid, ctx);
		if (cmd->pid == CHILD)
			process_cmd(ctx, cmd);
	}
}

static void	close_useless_pipes(t_exec *exec_data, t_node *curr_node)
{
	if (curr_node->prev)
		safe_close(&exec_data->prev_pipe_read);
	if (curr_node->next)
	{
		safe_close(&exec_data->pipe_fds[WRITE]);
		exec_data->prev_pipe_read = exec_data->pipe_fds[READ];
	}
}

void	start_children(t_context *ctx)
{
	t_node	*curr_cmd_node;

	curr_cmd_node = *ctx->head_cmd;
	while (curr_cmd_node)
	{
		if (curr_cmd_node->next)
			secure_pipe(ctx);
		process_cmd_if(ctx, curr_cmd_node);
		close_useless_pipes(ctx->exec_data, curr_cmd_node);
		curr_cmd_node = curr_cmd_node->next;
	}
}
