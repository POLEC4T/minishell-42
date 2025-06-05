/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_exec_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:31 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:11:00 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exec_pipes(t_exec *d)
{
	safe_close(&d->pipe_fds[READ]);
	safe_close(&d->pipe_fds[WRITE]);
	safe_close(&d->prev_pipe_read);
}
