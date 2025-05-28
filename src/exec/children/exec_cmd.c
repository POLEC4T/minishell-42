/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:48:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/28 21:06:13 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(t_context *ctx, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		ctx->exit_code = ft_echo(cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		ctx->exit_code = ft_cd(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ctx->exit_code = ft_pwd(cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ctx->exit_code = ft_export(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(ctx->head_env);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(ctx, cmd->args + 1);
}

/**
 * What I call a native cmd is all cmds except builtins
 */
static void	exec_native_cmd(t_context *ctx, t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_tab;

	cmd_path = get_cmd_path(ctx, cmd->args[0]);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
		exit_free(ctx);
	}
	env_tab = env_to_tabstr(ctx, cmd_path);
	execve(cmd_path, cmd->args, env_tab);
	free(cmd_path);
	ft_free_tab((void **)env_tab);
	exit_free(ctx);
}

void	exec_cmd(t_context *ctx, t_node *node_cmd)
{
	t_cmd	*cmd;

	cmd = cast_to_cmd(node_cmd->content);
	if (is_builtin_cmd(cmd->args[0]))
	{
		exec_builtin(ctx, cmd);
		if (!cmd->pid)
			exit_free(ctx);
		else
		{
			redirect(ctx->exec_data->saved_stdin, ctx->exec_data->saved_stdout,
				ctx);
			my_close(&ctx->exec_data->saved_stdin);
			my_close(&ctx->exec_data->saved_stdout);
		}
	}
	else
		exec_native_cmd(ctx, cmd);
}
