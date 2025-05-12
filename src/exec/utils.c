/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/12 09:52:42 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief redirects the standard input and output to the given file descriptors
 */
void	redirect(int input, int output, t_context *ctx)
{
	if (input != STDIN_FILENO)
		if (dup2(input, STDIN_FILENO) == -1)
			exit_free(ctx);
	if (output != STDOUT_FILENO)
		if (dup2(output, STDOUT_FILENO) == -1)
			exit_free(ctx);
}

void	secure_fork(int *pid, t_context *ctx)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_fprintf(STDERR_FILENO, "fork: %s\n", strerror(errno));
		exit_free(ctx);
	}
}

void	secure_pipe(t_context *ctx)
{
	int pipe_ret;

	pipe_ret = pipe(ctx->exec_data->pipe_fds);
	if (pipe_ret == -1)
	{
		ft_fprintf(STDERR_FILENO, "pipe: %s\n", strerror(errno));
		exit_free(ctx);
	}
}

/**
 * @returns ["", NULL]
 * @details made because the ft_split function returns [NULL] if the string is
 * empty
 */
char	**empty_split(void)
{
	char	**res;

	res = malloc(2 * sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = malloc(1 * sizeof(char));
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	res[0][0] = '\0';
	res[1] = NULL;
	return (res);
}
