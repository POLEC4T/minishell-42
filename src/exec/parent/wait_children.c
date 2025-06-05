/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 14:16:35 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(t_context *ctx, int status, int *already_printed)
{
	ctx->exit_code = WTERMSIG(status) + 128;
	if (WIFSIGNALED(status) && !(*already_printed))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			*already_printed = 1;
			if (WCOREDUMP(status))
				printf("Quit (core dumped)\n");
		}
		if (WTERMSIG(status) == SIGINT)
		{
			*already_printed = 1;
			printf("\n");
		}
	}
}

void	wait_children(t_context *ctx)
{
	int		status;
	t_node	*curr_node;
	t_cmd	*cmd;
	int		already_printed;

	already_printed = 0;
	curr_node = *ctx->head_cmd;
	status = EXIT_SUCCESS;
	while (curr_node)
	{
		cmd = cast_to_cmd(curr_node->content);
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				ctx->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				handle_signal(ctx, status, &already_printed);
		}
		curr_node = curr_node->next;
	}
}
