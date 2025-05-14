/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cmd_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:10:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 17:26:12 by mniemaz          ###   ########.fr       */
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

/**
 * @returns EXIT_FAILURE if one of the input redir files cannot be opened
 */
int	open_cmd_redirs(t_node *node_cmd)
{
	int			i;
	t_cmd		*cmd;
	t_redirect	*redir;
	int			exit_code;

	exit_code = EXIT_SUCCESS;
	cmd = cast_to_cmd(node_cmd->content);
	i = -1;
	if (cmd->redirects == NULL)
		return (EXIT_SUCCESS);
	while (cmd->redirects[++i])
	{
		redir = cmd->redirects[i];
		if (redir->redir_type == IN || redir->redir_type == HEREDOC)
		{
			redir->fd_in = open_infile(redir->filename);
			if (redir->fd_in == -1 && exit_code == EXIT_SUCCESS)
				exit_code = EXIT_FAILURE;
		}
		else if (redir->redir_type == OUT)
			redir->fd_out = open_outfile(redir->filename);
		else if (redir->redir_type == OUT_TRUNC)
			redir->fd_out = open_outfile_append(redir->filename);
	}
	return (exit_code);
}
