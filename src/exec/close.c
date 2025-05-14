/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:37:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 16:33:31 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_close(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = -2;
}

void	close_pipes(t_exec *d)
{
	my_close(&d->pipe_fds[READ]);
	my_close(&d->pipe_fds[WRITE]);
	my_close(&d->prev_pipe_read);
}

void	close_cmd_redirs(t_node *cmd_node)
{
	t_cmd	*cmd;
	int		i;

	cmd = cast_to_cmd(cmd_node->content);
	i = 0;
	if (cmd->redirects == NULL)
		return ;
	while (cmd->redirects[i])
	{
		my_close(&cmd->redirects[i]->fd_in);
		my_close(&cmd->redirects[i]->fd_out);
		i++;
	}
}

/**
 * @brief close all redirs of the chained list of commands
 * (does not close the pipe_fds)
 */
void	close_all_cmds_redirs(t_node **head_cmd)
{
	t_node	*cmd_node;

	cmd_node = *head_cmd;
	while (cmd_node)
	{
		close_cmd_redirs(cmd_node);
		cmd_node = cmd_node->next;
	}
}
