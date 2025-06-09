/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	ctx;

	(void)argv;
	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./minishell\n");
		return (EXIT_FAILURE);
	}
	init_context(&ctx);
	ft_export(&ctx, envp);
	process_lines(&ctx);
	exit_free(&ctx);
	return (EXIT_SUCCESS);
}
