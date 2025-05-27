/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/27 14:13:58 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *str, t_context *ctx)
{
	size_t	i;
	char	**spipe;
	t_node	*cmd_node;

	i = 0;
	spipe = ft_split_quote(str, "|");
	if (!spipe)
		return (EXIT_FAILURE);
	while (spipe[i])
	{
		cmd_node = ft_lstnew(NULL);
		if (!cmd_node)
		{
			ft_free_tab((void **)spipe);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(ctx->head_cmd, cmd_node);
		if (set_cmd_node_content(spipe[i], ctx, cmd_node) == EXIT_FAILURE)
		{
			ft_free_tab((void **)spipe);
			return (EXIT_FAILURE);
		}
		i++;
	}
	ft_free_tab((void **)spipe);
	return (EXIT_SUCCESS);
}

int	parsing_init(char *str, t_context *ctx)
{
	ctx->head_cmd = malloc(sizeof(t_node *));
	if (!ctx->head_cmd)
	{
		ft_fprintf(STDERR_FILENO, "parsing_init: %s\n", strerror(errno));
		exit_free(ctx);
	}
	*(ctx->head_cmd) = NULL;
	return (parsing(str, ctx));
}
