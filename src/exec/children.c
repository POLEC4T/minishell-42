/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/12 19:11:39 by mniemaz          ###   ########.fr       */
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
		ctx->exit_code = ft_exit(ctx, cmd->args + 1);
}

void	set_in_out_to_redirs(t_context *ctx, t_cmd *cmd, int *input,
		int *output)
{
	int	i;
	int	is_in_set;
	int	is_out_set;

	is_in_set = 0;
	is_out_set = 0;
	i = -1;
	while (cmd->redirects && cmd->redirects[++i])
	{
		if (cmd->redirects[i]->fd_in >= 0)
		{
			*input = cmd->redirects[i]->fd_in;
			is_in_set = 1;
		}
		if (cmd->redirects[i]->fd_out >= 0)
		{
			*output = cmd->redirects[i]->fd_out;
			is_out_set = 1;
		}
	}
	if (cmd->pid && is_in_set)
		ctx->exec_data->saved_stdin = dup(STDIN_FILENO);
	if (cmd->pid && is_out_set)
		ctx->exec_data->saved_stdout = dup(STDOUT_FILENO);
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

	input = -2;
	output = -2;
	if (node_cmd->next)
		output = ctx->exec_data->pipe_fds[WRITE];
	if (node_cmd->prev)
		input = ctx->exec_data->prev_pipe_read;
	cmd = cast_to_cmd(node_cmd->content);
	set_in_out_to_redirs(ctx, cmd, &input, &output);
	redirect(input, output, ctx);
}

/**
 * what I call a native cmd is all cmds except builtins
 */
static void	exec_native_cmd(t_context *ctx, t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_tab;

	cmd_path = get_cmd_path(ctx, cmd->args[0]);
	env_tab = env_to_tabstr(ctx->head_env);
	execve(cmd_path, cmd->args, env_tab);
	ft_fprintf(STDERR_FILENO, "execve: %s\n", strerror(errno));
	free(cmd_path);
	ft_free_tab((void **)env_tab);
	exit_free(ctx);
}

static void	exec_cmd(t_context *ctx, t_node *node_cmd)
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

static void	open_redirs(t_context *ctx, t_node *node_cmd)
{
	int			i;
	t_cmd		*cmd;
	t_redirect	*redir;

	cmd = cast_to_cmd(node_cmd->content);
	i = 0;
	if (cmd->redirects == NULL)
		return ;
	while (cmd->redirects[i])
	{
		redir = cmd->redirects[i];
		if (redir->redir_type == IN)
			redir->fd_in = open_infile(ctx, redir->filename);
		else if (redir->redir_type == OUT)
			redir->fd_out = open_outfile(redir->filename);
		else if (redir->redir_type == OUT_TRUNC)
			redir->fd_out = open_outfile_append(redir->filename);
		i++;
	}
}

/**
 * @brief this function processes
 * - the child (created the calling function in a fork)
 * - OR
 * - one builtin command in the parent process
 * @example
 * pitishell$ echo hello -> in the parent process
 * pitishell$ echo hello | grep hello -> all in children processes
 * pitishell$ cat file.txt -> in a child process
 */
void	process_cmd(t_context *ctx, t_node *node_cmd)
{
	t_cmd	*cmd;

	cmd = cast_to_cmd(node_cmd->content);
	open_redirs(ctx, node_cmd);
	set_curr_in_out(ctx, node_cmd);
	close_pipes(ctx->exec_data);
	close_fds_cmds(ctx->head_cmd);
	exec_cmd(ctx, node_cmd);
}
