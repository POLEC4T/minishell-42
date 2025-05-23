/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/23 17:04:52 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *str, t_node *prev_cmd, t_context *ctx)
{
	size_t	i;
	char	**spipe;
	t_node	*new_node;

	i = 0;
	new_node = NULL;
	spipe = ft_split(str, "|");
	if (!spipe)
		return (EXIT_FAILURE);
	while (spipe[i])
	{
		new_node = ft_lstnew((void *)split_cmd(spipe[i], ctx));
		if (!new_node->content)
		{
			ft_free_tab((void **)spipe);
			free(new_node);
			return (EXIT_FAILURE);
		}
		new_node->prev = prev_cmd;
		if (prev_cmd)
			prev_cmd->next = new_node;
		prev_cmd = new_node;
		if (!*ctx->head_cmd)
			*ctx->head_cmd = new_node;
		i++;
	}
	ft_free_tab((void **)spipe);
	return (EXIT_SUCCESS);
}

int	parsing_init(char *str, t_context *ctx)
{
	t_node	*prev_cmd;

	prev_cmd = NULL;
	ctx->head_cmd = malloc(sizeof(t_node *));
	if (!ctx->head_cmd)
	{
		ft_fprintf(STDERR_FILENO, "parsing_init: %s\n", strerror(errno));
		exit_free(ctx);
	}
	*(ctx->head_cmd) = NULL;
	return (parsing(str, prev_cmd, ctx));
}
