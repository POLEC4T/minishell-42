/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_cmd_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:41:45 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:10:56 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd_redirs(t_cmd *cmd)
{
	int		i;

	if (cmd == NULL || cmd->redirects == NULL)
		return ;
	i = 0;
	while (cmd->redirects[i])
	{
		safe_close(&cmd->redirects[i]->fd_in);
		safe_close(&cmd->redirects[i]->fd_out);
		i++;
	}
}
