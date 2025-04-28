/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/25 16:06:17 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_pipes(t_context *ctx)
{
	int	i;
	t_exec *d;

	d = ctx->exec_data;

	d->pipes = ft_calloc((d->nb_cmds - 1) + 1, sizeof(int *));
	if (!d->pipes)
	{
		msg("d->pipes malloc", ": ", strerror(errno), STDERR_FILENO);
		exit_free(ctx);
	}
	i = -1;
	while (++i < (d->nb_cmds - 1))
	{
		d->pipes[i] = malloc(2 * sizeof(int));
		if (!d->pipes[i])
		{
			msg("d->pipes[i] malloc", ": ", strerror(errno), STDERR_FILENO);
			exit_free(ctx);
		}
		d->pipes[i][READ] = -1;
		d->pipes[i][WRITE] = -1;
	}
	d->pipes[i] = NULL;
}

static void	create_pipes(t_context *ctx)
{
	int	i;
	int	pipe_ret;
	t_exec *d;

	d = ctx->exec_data;

	i = 0;
	alloc_pipes(ctx);
	while (i < (d->nb_cmds - 1))
	{
		pipe_ret = pipe(d->pipes[i]);
		if (pipe_ret == -1)
		{
			msg("pipe", ": ", strerror(errno), STDERR_FILENO);
			exit_free(ctx);
		}
		i++;
	}
}

void	init_exec(t_context *ctx)
{
	t_exec *d;

	d = ctx->exec_data;
	d->nb_cmds = ft_lstsize(*ctx->head_cmd);
	d->paths = get_paths(ctx);
	d->pids = malloc(d->nb_cmds * sizeof(int));
	if (!d->pids)
	{
		ft_fprintf(STDERR_FILENO, "exec: %s\n", strerror(errno));
		exit_free(ctx);
	}
	create_pipes(ctx);
}
