/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_cmds_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:42:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:10:53 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief close all redirs of the chained list of commands
 * (does not close the pipe_fds)
 */
void	close_all_cmds_redirs(t_node **head_cmd)
{
	t_node	*cmd_node;
	t_cmd	*cmd;

	cmd_node = *head_cmd;
	while (cmd_node)
	{
		cmd = cast_to_cmd(cmd_node->content);
		close_cmd_redirs(cmd);
		cmd_node = cmd_node->next;
	}
}
