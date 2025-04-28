/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/25 16:29:33 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_children(t_context *ctx)
{
	int		i_cmds;
	t_node	*curr_node;
	t_exec	*d;
	t_cmd	*curr_cmd;

	d = ctx->exec_data;
	curr_node = *ctx->head_cmd;
	i_cmds = 0;
	while (curr_node)
	{
		curr_cmd = cast_to_cmd(curr_node->content);
		secure_fork(&d->pids[i_cmds], ctx);
		if (!d->pids[i_cmds])
			process_child(ctx, curr_node, i_cmds);
		if (d->nb_cmds > 1)
		{
			if (i_cmds > 0)
				my_close(&d->pipes[i_cmds - 1][READ]);
			if (i_cmds < d->nb_cmds - 1)
				my_close(&d->pipes[i_cmds][WRITE]);
		}
		i_cmds++;
		curr_node = curr_node->next;
	}
}

int	wait_children(t_exec *d)
{
	int	status;
	int	i_pids;

	i_pids = -1;
	while (++i_pids < d->nb_cmds)
	{
		waitpid(d->pids[i_pids], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
