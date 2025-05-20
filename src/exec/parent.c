/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:23:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/19 17:52:44 by mniemaz          ###   ########.fr       */
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
		process_cmd(ctx, cmd_node);
	else
	{
		secure_fork(&cmd->pid, ctx);
		if (!cmd->pid)
		{
			// todo: secure signals
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			process_cmd(ctx, cmd_node);
		}
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

/**
 * if open_cmd_redirs fails
 * - we don't want to process the command
 * - we wait the previous children in order to not close the pipes before
 * 		they are used
 *   -> if we don't wait the children, this command throws a SIGPIPE :
 * 		echo oui | echo bye > test_no_perm
 */
void	start_children(t_context *ctx)
{
	t_node	*curr_node;

	curr_node = *ctx->head_cmd;
	while (curr_node)
	{
		if (curr_node->next)
			secure_pipe(ctx);
		if (open_cmd_redirs(curr_node) == EXIT_SUCCESS)
			process_cmd_if(ctx, curr_node);
		else
		{
			wait_children(ctx);
			(cast_to_cmd(curr_node->content))->exit_code = EXIT_FAILURE;
		}
		close_useless_pipes(ctx->exec_data, curr_node);
		close_cmd_redirs(curr_node);
		curr_node = curr_node->next;
	}
}

void	wait_children(t_context *ctx)
{
	int		status;
	t_node	*curr_node;
	t_cmd	*cmd;

	status = 0;
	curr_node = *ctx->head_cmd;
	while (curr_node)
	{
		cmd = cast_to_cmd(curr_node->content);
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				ctx->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				ctx->exit_code = WTERMSIG(status) + 128;
				printf("child exited by signal %d\n", WTERMSIG(status));
				usleep(500000);
			}
		}
		else if (cmd->exit_code)
			ctx->exit_code = cmd->exit_code;
		curr_node = curr_node->next;
	}
}
