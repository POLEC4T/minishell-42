/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:10:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 10:45:26 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(t_context *ctx, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
		exit_free(ctx);
	}
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

void	open_redirs(t_context *ctx, t_node *node_cmd)
{
	int			i;
	t_cmd		*cmd;
	t_redirect	*redir;

	cmd = cast_to_cmd(node_cmd->content);
	i = 0;
	if (cmd->redirects == NULL)
		return ;
	while (cmd->redirects[i])
	{
		redir = cmd->redirects[i];
		if (redir->redir_type == IN)
			redir->fd_in = open_infile(ctx, redir->filename);
		else if (redir->redir_type == OUT)
			redir->fd_out = open_outfile(redir->filename);
		else if (redir->redir_type == OUT_TRUNC)
			redir->fd_out = open_outfile_append(redir->filename);
		i++;
	}
}
