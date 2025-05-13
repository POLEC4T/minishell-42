/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 10:29:13 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_node(t_node **head_cmd, t_node *prev_cmd, t_node *new_node,
		char *spipe)
{
	new_node = ft_lstnew((void *)split_cmd(spipe));
	new_node->prev = prev_cmd;
	if (prev_cmd)
		prev_cmd->next = new_node;
	prev_cmd = new_node;
	if (!*head_cmd)
		*head_cmd = new_node;
}

t_node	**parsing(char *str)
{
	size_t	i;
	t_node	**head_cmd;
	t_node	*prev_cmd;
	t_node	*new_node;
	char	**spipe;

	i = 0;
	head_cmd = NULL;
	prev_cmd = NULL;
	new_node = NULL;
	head_cmd = malloc(sizeof(t_node *));
	*head_cmd = NULL;
	spipe = ft_split(str, "|");
	if (!spipe)
		return (NULL);
	while (spipe[i])
	{
		init_node(head_cmd, prev_cmd, new_node, spipe[i]);
		i++;
	}
	ft_free_tab((void **)spipe);
	return (head_cmd);
}
