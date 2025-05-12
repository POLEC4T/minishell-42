/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/12 17:34:28 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief processes the command, but not always the same way
 * @details if the command is a builtin and there is no other commands,
 * it will be executed in the parent process. Else, it will be executed 
 * in a child process
 */
static void	process_cmd_if(t_context *ctx, t_node *curr_node)
{
	t_cmd	*curr_cmd;
	int		is_builtin_and_alone;

	curr_cmd = cast_to_cmd(curr_node->content);
	is_builtin_and_alone = !curr_node->next && !curr_node->prev
		&& is_builtin_cmd(curr_cmd->args[0]);
	if (is_builtin_and_alone)
		process_cmd(ctx, curr_node);
	else
	{
		secure_fork(&curr_cmd->pid, ctx);
		if (!curr_cmd->pid)
			process_cmd(ctx, curr_node);
	}
}

static void	close_useless_pipes(t_exec *exec_data, t_node *curr_node)
{
	if (curr_node->prev)
		my_close(&exec_data->prev_pipe_read);
	if (curr_node->next)
	{
		my_close(&exec_data->pipe_fds[WRITE]);
		exec_data->prev_pipe_read = exec_data->pipe_fds[READ];
	}
}

void	start_children(t_context *ctx)
{
	t_node	*curr_node;

	curr_node = *ctx->head_cmd;
	while (curr_node)
	{
		if (curr_node->next)
			secure_pipe(ctx);
		process_cmd_if(ctx, curr_node);
		close_useless_pipes(ctx->exec_data, curr_node);
		curr_node = curr_node->next;
	}
}

void	wait_children(t_context *ctx)
{
	int		status;
	t_node	*curr_node;
	t_cmd	*cmd;

	curr_node = *ctx->head_cmd;
	while (curr_node)
	{
		cmd = cast_to_cmd(curr_node->content);
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				ctx->exit_code = WEXITSTATUS(status);
		}
		curr_node = curr_node->next;
	}
}
