/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/02 16:22:39 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_parsing(void **to_free)
{
	ft_fprintf(STDERR_FILENO, "parsing: %s\n", strerror(errno));
	if (to_free)
		ft_free_tab(to_free);
	return (EXIT_FAILURE);
}

int	parsing(char *str, t_context *ctx)
{
	size_t	i;
	char	**spipe;
	t_node	*cmd_node;

	i = -1;
	spipe = ft_split_quote(str, "|");
	if (!spipe)
		return (err_parsing(NULL));
	while (spipe[++i])
	{
		cmd_node = ft_lstnew(NULL);
		if (!cmd_node)
			return (err_parsing((void **)spipe));
		ft_lstadd_back(ctx->head_cmd, cmd_node);
		if (set_cmd_node_content(spipe[i], ctx, cmd_node) == EXIT_FAILURE)
		{
			ft_free_tab((void **)spipe);
			return (EXIT_FAILURE);
		}
	}
	ft_free_tab((void **)spipe);
	return (EXIT_SUCCESS);
}
