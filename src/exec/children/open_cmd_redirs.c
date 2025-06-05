/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cmd_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:10:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 10:35:09 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

static int	open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

/**
 * @brief open the output file in append mode
 */
static int	open_outfile_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

static int	open_cmd_redir(t_redirect *redir)
{
	if (redir->redir_type == IN || redir->redir_type == HEREDOC
		|| redir->redir_type == HEREDOC_NO_INTER)
	{
		redir->fd_in = open_infile(redir->filename);
		if (redir->fd_in == -1)
			return (EXIT_FAILURE);
	}
	else if (redir->redir_type == OUT)
	{
		redir->fd_out = open_outfile(redir->filename);
		if (redir->fd_out == -1)
			return (EXIT_FAILURE);
	}
	else if (redir->redir_type == OUT_TRUNC)
	{
		redir->fd_out = open_outfile_append(redir->filename);
		if (redir->fd_out == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_cmd_redirs(t_cmd *cmd)
{
	int		i;

	if (cmd->redirects == NULL)
		return (EXIT_SUCCESS);
	i = -1;
	while (cmd->redirects[++i])
		if (open_cmd_redir(cmd->redirects[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
