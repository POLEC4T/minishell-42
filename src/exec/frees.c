/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/23 17:25:01 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(int error_status, t_data *data)
{
	if (data)
	{
		close_fds_and_pipes(data);
		if (data->cmd != NULL)
			ft_free_tab((void **)data->cmd);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		if (data->paths != NULL)
			ft_free_tab((void **)data->paths);
		if (data->pids != NULL)
			free(data->pids);
		if (data->pipes != NULL)
			ft_free_tab((void **)data->pipes);
		if (data->is_here_doc)
			unlink(HEREDOC_FILENAME);
		
	}
	exit(error_status);
}
