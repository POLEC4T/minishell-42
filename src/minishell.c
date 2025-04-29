/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/29 16:50:16 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_init_exec(t_context *ctx)
{
	ctx->exec_data = malloc (sizeof(t_exec));
	if (!ctx->exec_data)
	{
		ft_fprintf(STDERR_FILENO, "malloc: %s\n", strerror(errno));
		exit_free(ctx);
	}
	ctx->exec_data->nb_cmds = -1;
	ctx->exec_data->paths = NULL;
	ctx->exec_data->cmd_path = NULL;
	ctx->exec_data->prev_pipe_read = -2;
	ctx->exec_data->pipe_fds[READ] = -2;
	ctx->exec_data->pipe_fds[WRITE] = -2;
}

void	init_context(t_context *context)
{
	context->head_env = malloc(sizeof(t_node *));
	if (!context->head_env)
		exit(EXIT_FAILURE);
	(*(context->head_env)) = NULL;
	context->head_cmd = malloc(sizeof(t_node *));
	if (!context->head_cmd)
		exit(EXIT_FAILURE);
	(*(context->head_cmd)) = NULL;
	context->head_token = NULL;
	context->exit_code = 0;
	clean_init_exec(context);
}

void prep_fake_cmd(t_context *ctx, char *args, int fd_in, int fd_out)
{
	t_node	*cmd;
	t_cmd	*fake_cmd;
	t_redirect *redirs;


	
	cmd = ft_lstnew(NULL);
	if (!cmd)
		exit(EXIT_FAILURE);
	fake_cmd = malloc(sizeof(t_cmd));
	if (!fake_cmd)
		exit(EXIT_FAILURE);
	fake_cmd->args = ft_split(args, " ");
	if (!fake_cmd->args)
		exit(EXIT_FAILURE);
	fake_cmd->redirects = fd_in;
	fake_cmd->pid = -2;
	cmd->content = fake_cmd;
	ft_lstadd_back(ctx->head_cmd, cmd);
}

void prep_fake_cmds(t_context *ctx)
{
	prep_fake_cmd(ctx, "echo oui", "Makefile", IN); // not working ????? \n a chaque fin de ligne
	prep_fake_cmd(ctx, "cat", -2, -2); // not working ????? \n a chaque fin de ligne
}

void print_cmd(t_node *cmd)
{
	t_cmd	*cmd_content;

	cmd_content = cast_to_cmd(cmd->content);
	if (!cmd_content)
		return ;
	printf("Command: ");
	for (int i = 0; cmd_content->args && cmd_content->args[i]; i++)
		printf("%s ", cmd_content->args[i]);
	if (cmd_content->fd_in != -2)
		printf("    -> fd_in: %d", cmd_content->fd_in);
	if (cmd_content->fd_out != -2)
		printf("    -> fd_out: %d", cmd_content->fd_out);
	printf("\n");
}

void	minishell(char **envp)
{
	t_context ctx;
	init_context(&ctx);
	ft_export(&ctx, envp);

	prep_fake_cmds(&ctx);
    ft_exec(&ctx);
	
	exit_free(&ctx);
}