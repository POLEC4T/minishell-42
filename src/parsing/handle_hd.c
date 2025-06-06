/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:53 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 19:10:23 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_in_file(int hd_fd, char *eof, t_context *ctx,
		t_redir_type redir_type)
{
	char	*line;

	while (g_signal == 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line && g_signal == 0)
		{
			write(STDERR_FILENO, "\n", 1);
			ft_fprintf(STDERR_FILENO, "warning: here-document \
delimited by end-of-file (wanted `%s')\n", eof);
			break ;
		}
		if (!line || !ft_strncmp(rm_last_char(line), eof, ft_strlen(eof) + 1))
			break ;
		if (redir_type != HEREDOC_NO_INTER)
			line = expand_line(line, ctx, HD);
		ft_putendl_fd(line, hd_fd);
		free(line);
	}
	close(hd_fd);
	free(eof);
	free(line);
}

static int	wait_hd_child(t_context *ctx)
{
	int	status;

	status = 0;
	waitpid(ctx->hd_pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
		{
			if (WEXITSTATUS(status) > 128)
			{
				write(STDERR_FILENO, "\n", 1);
				g_signal = WEXITSTATUS(status) - 128;
			}
			ctx->exit_code = WEXITSTATUS(status);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	err_start_hd_child(t_context *ctx, char *eof, int is_child)
{
	free(eof);
	ft_fprintf(STDERR_FILENO, "start_hd_child: %s\n", strerror(errno));
	if (is_child)
		ctx->exit_code = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

/**
 * The child returns EXIT_FAILURE in every case in order to free all in parent
 * functions (it exits in process_lines function)
 */
static int	start_hd_child(t_context *ctx, t_redirect **redir, char *eof)
{
	int	hd_fd;

	ctx->exit_code = EXIT_SUCCESS;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (err_start_hd_child(ctx, eof, 0));
	ctx->hd_pid = fork();
	if (ctx->hd_pid == -1)
		return (err_start_hd_child(ctx, eof, 0));
	if (ctx->hd_pid == CHILD)
	{
		if (setup_hd_signals() == EXIT_FAILURE)
			return (err_start_hd_child(ctx, eof, 1));
		hd_fd = open((*redir)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (hd_fd == -1)
			return (err_start_hd_child(ctx, eof, 1));
		write_in_file(hd_fd, eof, ctx, (*redir)->redir_type);
		return (EXIT_FAILURE);
	}
	free(eof);
	return (EXIT_SUCCESS);
}

int	handle_hd(t_context *ctx, char *str, size_t *i, t_redirect **redir)
{
	char	*eof;

	(*redir)->filename = get_unique_filename(HD_BASENAME);
	if (!(*redir)->filename)
		return (return_int_failure_msg("handle_hd: get_unique_filename"));
	eof = malloc((redir_word_len(str) + 1) * sizeof(char));
	if (!eof)
		return (return_int_failure_msg("handle_hd: malloc eof"));
	*i += extract_redir_word(str + *i, eof);
	if (start_hd_child(ctx, redir, eof) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (wait_hd_child(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
