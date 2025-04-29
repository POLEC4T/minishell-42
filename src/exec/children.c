/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/29 14:59:29 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void exec_builtin(t_context *ctx, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		ft_echo(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd(cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(ctx->head_env);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(ctx, cmd->args + 1);
}

/**
 * @brief set the current input and output file descriptors
 * @details if fd_in is set in the command, it will be used as input
 * else if i_cmds > 0, the input will be the output of the previous command
 * if fd_out is set in the command, it will be used as output
 * else if [not last cmd], the output will be the input of the next command
 */
static void	set_curr_in_out(t_context *ctx, t_node *node_cmd)
{
	int		input;
	int		output;
	t_cmd	*cmd;

	cmd = cast_to_cmd(node_cmd->content);
	input = STDIN_FILENO;
	output = STDOUT_FILENO;
	if (cmd->fd_in >= 0)
		input = cmd->fd_in;
	else if (node_cmd->prev)
		input = ctx->exec_data->prev_pipe_read;
	if (cmd->fd_out >= 0)
		output = cmd->fd_out;
	else if (node_cmd->next)
		output = ctx->exec_data->pipe_fds[WRITE];
	redirect(input, output, ctx);
}

static void	exec_cmd(t_context *ctx, t_cmd *cmd)
{
	t_exec	*d;

	d = ctx->exec_data;
	
	if (is_builtin_cmd(cmd->args[0]))
		exec_builtin(ctx, cmd);
	else 
	{
		d->cmd_path = get_cmd_path(ctx, cmd->args[0]);
		execve(d->cmd_path, cmd->args, env_to_tabstr(ctx->head_env));
		ft_fprintf(STDERR_FILENO, "exec: %s", strerror(errno));
	}
	exit_free(ctx);
}

void	process_child(t_context *ctx, t_node *node_cmd)
{
	t_cmd	*cmd;

	cmd = cast_to_cmd(node_cmd->content);
	set_curr_in_out(ctx, node_cmd);
	close_pipes(ctx->exec_data);
	close_fds_cmds(ctx->head_cmd);
	exec_cmd(ctx, cmd);
}
