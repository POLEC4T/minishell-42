/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 11:44:37 by mniemaz          ###   ########.fr       */
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
	if (is_cmd_a_single_builtin)
		process_cmd(ctx, cmd);
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		{
			ft_fprintf(STDERR_FILENO, "process_cmd_if: %s\n", strerror(errno));
			ctx->exit_code = EXIT_FAILURE;
			exit_free(ctx);
		}
		secure_fork(&cmd->pid, ctx);
		if (cmd->pid == CHILD)
			process_cmd(ctx, cmd);
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
