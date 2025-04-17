/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:11:38 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 14:13:05 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

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

int	define_token(t_token token)
{
	if (ft_strstr(token.data, "<<") == 1)
		return (HEREDOC);
	if (ft_strstr(token.data, ">") == 1 || ft_strstr(token.data, "<") == 1)
		return (OPERATOR);
	if (ft_strstr(token.data, "|") == 1)
		return (PIPE);
	if (ft_strstr(token.data, "-") == 1)
		return (FLAG);
	if (token.previous)
	{
		if (token.previous->type == HEREDOC)
			return (DELIMITER);
		if (token.previous->type == COMMAND)
			return (ARGUMENT);
		if (token.previous->type == PIPE)
			return (COMMAND);
		if (token.previous->type == DELIMITER)
			return (COMMAND);
	}
	if(!token.previous)
		return(COMMAND);
	return (FILES);
}
