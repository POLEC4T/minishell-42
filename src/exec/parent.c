/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/04 11:21:27 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_children(t_context *ctx)
{
	t_node	*curr_node;
	t_exec	*d;
	t_cmd	*curr_cmd;

	d = ctx->exec_data;
	curr_node = *ctx->head_cmd;
	while (curr_node)
	{
		curr_cmd = cast_to_cmd(curr_node->content);
		if (curr_node->next)
			secure_pipe(ctx);
		if (!is_builtin_cmd(curr_cmd->args[0]))
			secure_fork(&curr_cmd->pid, ctx);
		if (!curr_cmd->pid || is_builtin_cmd(curr_cmd->args[0]))
			process_cmd(ctx, curr_node);
		if (curr_node->next)
		{
			my_close(&d->pipe_fds[WRITE]);
			d->prev_pipe_read = d->pipe_fds[READ];
		}
		if (curr_node->prev)
			my_close(&d->prev_pipe_read);
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
