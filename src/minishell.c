/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/06 13:39:21 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_init_exec(t_context *ctx)
{
	ctx->exec_data = malloc(sizeof(t_exec));
	if (!ctx->exec_data)
	{
		ft_fprintf(STDERR_FILENO, "malloc: %s\n", strerror(errno));
		exit_free(ctx);
	}
	ctx->exec_data->nb_cmds = -1;
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
	context->exit_code = 0;
	clean_init_exec(context);
}

void	prep_fake_cmd(t_context *ctx, char *args, t_redirect **redirs)
{
	t_node	*cmd;
	t_cmd	*fake_cmd;

	cmd = ft_lstnew(NULL);
	if (!cmd)
		exit(EXIT_FAILURE);
	fake_cmd = malloc(sizeof(t_cmd));
	if (!fake_cmd)
		exit(EXIT_FAILURE);
	fake_cmd->args = ft_split(args, " ");
	if (!fake_cmd->args)
		exit(EXIT_FAILURE);
	fake_cmd->redirects = redirs;
	fake_cmd->pid = -2;
	cmd->content = fake_cmd;
	ft_lstadd_back(ctx->head_cmd, cmd);
}

t_redirect	**prep_fake_redirs(char **filenames, t_redir_type *types)
{
	t_redirect	**redirs;
	int			i;

	if (!filenames || !types)
		return (NULL);
	redirs = malloc(sizeof(t_redirect *) * (ft_tablen((void **)filenames) + 1));
	i = 0;
	while (filenames[i])
	{
		redirs[i] = malloc(sizeof(t_redirect));
		redirs[i]->filename = filenames[i];
		redirs[i]->redir_type = types[i];
		redirs[i]->fd_in = -2;
		redirs[i]->fd_out = -2;
		i++;
	}
	redirs[i] = NULL;
	return (redirs);
}

void	prep_fake_cmds(t_context *ctx)
{
	prep_fake_cmd(ctx, "mkdir -p testdir/a/b/c/d", prep_fake_redirs((char *[]){NULL},
			(t_redir_type[]){}));
	prep_fake_cmd(ctx, "cd testdir/a/b/c/d", prep_fake_redirs((char *[]){NULL},
			(t_redir_type[]){}));
	prep_fake_cmd(ctx, "rm -r ../../../../a", prep_fake_redirs((char *[]){NULL},
			(t_redir_type[]){}));
	prep_fake_cmd(ctx, "cd ..", prep_fake_redirs((char *[]){NULL},
			(t_redir_type[]){}));
	// prep_fake_cmd(ctx, "export dfsaf4334ff", prep_fake_redirs((char *[]){NULL},
	// 		(t_redir_type[]){}));
	// prep_fake_cmd(ctx, "cd ..", prep_fake_redirs((char *[]){"Makefile",
	// NULL},
	// 		(t_redir_type[]){IN}));
	// prep_fake_cmd(ctx, "cat test", prep_fake_redirs((char *[]){"test",
	// 		NULL}, (t_redir_type[]){IN}));
	// prep_fake_cmd(ctx, "ls", NULL);
}

void	print_cmd(t_node *cmd)
{
	t_cmd	*cmd_content;

	cmd_content = cast_to_cmd(cmd->content);
	if (!cmd_content)
		return ;
	printf("Command: ");
	for (int i = 0; cmd_content->args && cmd_content->args[i]; i++)
		printf("%s ", cmd_content->args[i]);
	if (cmd_content->pid != -2)
		printf("-> pid: %d", cmd_content->pid);
	printf("\n");
}

void	minishell(char **envp)
{
	(void)envp;
	t_context ctx;
	init_context(&ctx);
	ft_export(&ctx, envp);
	
	read_token(&ctx);
	//prep_fake_cmds(&ctx);
	//ft_exec(&ctx);
	exit_free(&ctx);
}