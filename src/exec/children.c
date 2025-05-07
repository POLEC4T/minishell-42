/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 15:54:22 by mniemaz          ###   ########.fr       */
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
	int		i;

	cmd = cast_to_cmd(node_cmd->content);
	input = STDIN_FILENO;
	output = STDOUT_FILENO;
	i = 0;
	if (node_cmd->next)
		output = ctx->exec_data->pipe_fds[WRITE];
	if (node_cmd->prev)
		input = ctx->exec_data->prev_pipe_read;
	while (cmd->redirects && cmd->redirects[i])
	{
		if (cmd->redirects[i]->fd_in >= 0)
			input = cmd->redirects[i]->fd_in;
		if (cmd->redirects[i]->fd_out >= 0)
			output = cmd->redirects[i]->fd_out;
		i++;
	}
	redirect(input, output, ctx);
}

static void	exec_cmd(t_context *ctx, t_node *node_cmd)
{
	t_exec	*d;
	t_cmd	*cmd;

	d = ctx->exec_data;
	cmd = cast_to_cmd(node_cmd->content);
	if (is_builtin_cmd(cmd->args[0]))
	{
		exec_builtin(ctx, cmd);
		if (node_cmd->next || node_cmd->prev)
			exit_free(ctx);
	}
	else
	{
		execve(get_cmd_path(ctx, cmd->args[0]), cmd->args,
			env_to_tabstr(ctx->head_env));
		ft_fprintf(STDERR_FILENO, "exec: %s", strerror(errno));
		exit_free(ctx);
	}
}
// TODO put opens in another file
int	open_infile(t_context *ctx, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
		exit_free(ctx);
	}
	return (fd);
}

int	open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

/**
 * * @brief open the output file in append mode
 */
int	open_outfile_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

static void	open_redirs(t_context *ctx, t_node *node_cmd)
{
	int			i;
	t_cmd		*cmd;
	t_redirect	*redir;

	cmd = cast_to_cmd(node_cmd->content);
	i = 0;
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
	if (cmd->redirects)
		open_redirs(ctx, node_cmd);
	set_curr_in_out(ctx, node_cmd);
	close_pipes(ctx->exec_data);
	close_fds_cmds(ctx->head_cmd);
	exec_cmd(ctx, node_cmd);
}
