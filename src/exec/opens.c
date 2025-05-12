/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:10:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/12 19:14:03 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_context *ctx, char *filename)
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

int	open_outfile(char *filename)
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
int	open_outfile_append(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}