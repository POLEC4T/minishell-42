/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cmd_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:53:56 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 18:26:33 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get the input file descriptor of the command and save the
 * stdin fd if the command is a in the parent process
 */
int	get_redir_in(t_context *ctx, t_cmd *cmd)
{
	int	i;
	int	input;

	input = UNDEFINED_INT;
	i = -1;
	while (cmd->redirects && cmd->redirects[++i])
		if (cmd->redirects[i]->fd_in >= 0)
			input = cmd->redirects[i]->fd_in;
	if (cmd->pid && input >= 0)
	{
		ctx->exec_data->saved_stdin = dup(STDIN_FILENO);
		if (ctx->exec_data->saved_stdin == -1)
		{
			ft_fprintf(STDERR_FILENO, "dup: %s\n", strerror(errno));
			ctx->exit_code = EXIT_FAILURE;
			exit_free(ctx);
		}
	}
	return (input);
}

/**
 * @brief get the output file descriptor of the command and save the
 * stdout fd if the command is a in the parent process
 */
int	get_redir_out(t_context *ctx, t_cmd *cmd)
{
	int	i;
	int	output;

	output = UNDEFINED_INT;
	i = -1;
	while (cmd->redirects && cmd->redirects[++i])
		if (cmd->redirects[i]->fd_out >= 0)
			output = cmd->redirects[i]->fd_out;
	if (cmd->pid && output >= 0)
	{
		ctx->exec_data->saved_stdout = dup(STDOUT_FILENO);
		if (ctx->exec_data->saved_stdout == -1)
		{
			ft_fprintf(STDERR_FILENO, "dup: %s\n", strerror(errno));
			ctx->exit_code = EXIT_FAILURE;
			exit_free(ctx);
		}
	}
	return (output);
}

/**
 * @brief duplicates the fd in and out of the command
 * redirections and pipes
 */
void	dup_cmd_redirs(t_context *ctx, t_node *node_cmd)
{
	int	input;
	int	output;

	input = get_redir_in(ctx, cast_to_cmd(node_cmd->content));
	output = get_redir_out(ctx, cast_to_cmd(node_cmd->content));
	if (input == UNDEFINED_INT && ctx->exec_data->prev_pipe_read >= 0)
		input = ctx->exec_data->prev_pipe_read;
	if (output == UNDEFINED_INT && ctx->exec_data->pipe_fds[WRITE] >= 0)
		output = ctx->exec_data->pipe_fds[WRITE];
	redirect(input, output, ctx);
}
