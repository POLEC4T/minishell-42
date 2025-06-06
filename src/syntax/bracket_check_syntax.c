/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_check_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:27:26 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/06 10:29:55 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	brackets_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] && str[i] != '|')
			{
				if (str[i] != ' ')
					break ;
				i++;
			}
			if (str[i] == '|' || !str[i])
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
