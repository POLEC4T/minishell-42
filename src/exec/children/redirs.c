/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:53:56 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 11:21:58 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get the input file descriptor of the command and save the current
 * stdin if the command is a in the parent process
 */
int	get_redir_in(t_context *ctx, t_cmd *cmd)
{
	int	i;
	int input;

	input = -2;
	i = -1;
	while (cmd->redirects && cmd->redirects[++i])
		if (cmd->redirects[i]->fd_in >= 0)
			input = cmd->redirects[i]->fd_in;
	if (cmd->pid && input >= 0)
		ctx->exec_data->saved_stdin = dup(STDIN_FILENO);
	return (input);
}

/**
 * @brief get the output file descriptor of the command and save the current
 * stdout if the command is a in the parent process
 */
int	get_redir_out(t_context *ctx, t_cmd *cmd)
{
	int	i;
	int output;

	output = -2;
	i = -1;
	while (cmd->redirects && cmd->redirects[++i])
		if (cmd->redirects[i]->fd_out >= 0)
			output = cmd->redirects[i]->fd_out;
	if (cmd->pid && output >= 0)
		ctx->exec_data->saved_stdout = dup(STDOUT_FILENO);
	return (output);
}

/**
 * @brief set the current input and output file descriptors
 * @details if fd_in is set in the command, it will be used as input
 * else if i_cmds > 0, the input will be the output of the previous command
 * if fd_out is set in the command, it will be used as output
 * else if [not last cmd], the output will be the input of the next command
 */
void	dup_redirs(t_context *ctx, t_node *node_cmd)
{
	int		input;
	int		output;

	input = get_redir_in(ctx, cast_to_cmd(node_cmd->content));
	output = get_redir_out(ctx, cast_to_cmd(node_cmd->content));
	if (node_cmd->next && input == -2)
		output = ctx->exec_data->pipe_fds[WRITE];
	if (node_cmd->prev && input == -2)
		input = ctx->exec_data->prev_pipe_read;
	redirect(input, output, ctx);
}
