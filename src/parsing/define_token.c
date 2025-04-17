/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:11:38 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 16:06:57 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	define_token(t_node *node)
{
	t_token	*token;
	t_token	*prev_token;

	token = cast_to_token(node->content);
	if (ft_strstr(token->data, "<<") == 1)
		return (HEREDOC);
	if (ft_strstr(token->data, ">") == 1 || ft_strstr(token->data, "<") == 1)
		return (OPERATOR);
	if (ft_strstr(token->data, "|") == 1)
		return (PIPE);
	if (ft_strstr(token->data, "-") == 1)
		return (FLAG);
	if (node->prev)
	{
		prev_token = cast_to_token(node->prev->content);
		if (prev_token->type == HEREDOC)
			return (DELIMITER);
		if (prev_token->type == COMMAND)
			return (ARGUMENT);
		if (prev_token->type == PIPE)
			return (COMMAND);
		if (prev_token->type == DELIMITER)
			return (COMMAND);
	}
	if (!node->prev)
		return (COMMAND);
	return (FILES);
}
