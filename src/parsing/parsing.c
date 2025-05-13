/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 13:28:34 by nle-gued         ###   ########.fr       */
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

t_node	**parsing(char *str, t_node **head_cmd, t_node *prev_cmd,
		t_node *new_node)
{
	size_t	i;
	char	**spipe;

	i = 0;
	spipe = ft_split(str, "|");
	if (!spipe)
		return (NULL);
	while (spipe[i])
	{
		new_node = ft_lstnew((void *)split_cmd(spipe[i]));
		new_node->prev = prev_cmd;
		if (prev_cmd)
			prev_cmd->next = new_node;
		prev_cmd = new_node;
		if (!*head_cmd)
			*head_cmd = new_node;
		i++;
	}
	ft_free_tab((void **)spipe);
	return (head_cmd);
}

t_node	**parsing_init(char *str)
{
	t_node **head_cmd;
	t_node *prev_cmd;
	t_node *new_node;

	head_cmd = NULL;
	prev_cmd = NULL;
	new_node = NULL;
	head_cmd = malloc(sizeof(t_node *));
	*head_cmd = NULL;

	return (parsing(str, head_cmd, prev_cmd, new_node));
}
