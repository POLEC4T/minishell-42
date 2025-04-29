/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:37:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/29 13:12:04 by mniemaz          ###   ########.fr       */
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
}
/**
 * @brief close all file descriptors of the chained list of commands
 * (does not close the pipe_fds)
 */
void	close_fds_cmds(t_node **head_cmd)
{
	t_node	*cmd;
	t_cmd	*cmd_content;

	cmd = *head_cmd;
	while (cmd)
	{
		cmd_content = cast_to_cmd(cmd->content);
		my_close(&cmd_content->fd_in);
		my_close(&cmd_content->fd_out);
		cmd = cmd->next;
	}
}
