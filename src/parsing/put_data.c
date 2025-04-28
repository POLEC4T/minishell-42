/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:38:11 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/24 15:14:58 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strcount(char *str, char stop)
{
	size_t	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		while (str[i] == str[0])
			i++;
		return (i);
	}
	if (str[i] == '|')
		return (1);
	while (str[i] && str[i] != stop && str[i] != '"')
	{
		if (str[i] == '|')
			return (i);
		if (str[i] == '<' || str[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

void	put_exec(char *str, t_node *node, char stop)
{
	size_t	length;
	size_t	i;
	t_token *token;
	
	node->content = malloc(sizeof(t_token));
	
	length = strcount(str, stop);
	token = cast_to_token(node->content);
	token->data = malloc((length + 1) * sizeof(char));
	if (!token->data)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < length)
	{
		token->data[i] = str[i];
		i++;
	}
	token->data[length] = '\0';
	token->type = define_token(node);
}
