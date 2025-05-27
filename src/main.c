/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/21 10:52:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_fprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		return (EXIT_FAILURE);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}

// int main(void)
// {
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		pause();
// 	}
// 	else
// 	{
// 		int status;
// 		waitpid(pid, &status, 0);
// 		if (WIFSIGNALED(status))
// 			printf("child exited by signal %d\n", WTERMSIG(status));
// 	}
// }
