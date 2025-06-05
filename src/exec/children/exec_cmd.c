/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:48:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:10:35 by mniemaz          ###   ########.fr       */
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
		ctx->exit_code = ft_unset(ctx, cmd->args + 1);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ctx->exit_code = ft_env(ctx->head_env);
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

	if (cmd->args[0] == NULL)
		exit_free(ctx);
	cmd_path = get_cmd_path(ctx, cmd->args[0]);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
		exit_free(ctx);
	}
	env_tab = env_to_tabstr(ctx, cmd_path);
	execve(cmd_path, cmd->args, env_tab);
	ft_fprintf(STDERR_FILENO, "%s: %s\n", cmd->args[0], strerror(errno));
	free(cmd_path);
	ft_free_tab((void **)env_tab);
	ctx->exit_code = EXIT_FAILURE;
	exit_free(ctx);
}

void	exec_cmd(t_context *ctx, t_cmd *cmd)
{
	t_exec	*data;

	data = ctx->exec_data;
	if (is_builtin_cmd(cmd->args[0]))
	{
		exec_builtin(ctx, cmd);
		if (cmd->pid == CHILD)
			exit_free(ctx);
		else
		{
			redirect(data->saved_stdin, data->saved_stdout, ctx);
			safe_close(&data->saved_stdin);
			safe_close(&data->saved_stdout);
		}
	}
	else
		exec_native_cmd(ctx, cmd);
}
