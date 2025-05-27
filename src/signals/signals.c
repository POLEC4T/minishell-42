/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:12:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/27 15:16:30 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_sigint_handler(int sigint)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = sigint;
}

/**
 * using sigaction to allow gnl to be interrupted by a signal,
 * thanks to the sa_flags = 0
 */
void	install_sigint_handler(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	// todo secure signal
	sigaction(SIGINT, &sa, NULL);
}

void	hd_sigint_handler(int sig)
{
	g_signal = sig;
}