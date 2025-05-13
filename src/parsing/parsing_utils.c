/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:55:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 11:00:27 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_spaces(char *str, size_t i)
{
	while (str[i] == ' ' && str[i])
		i++;
	return (i);
}

size_t	skip_redirection(char *str, size_t i)
{
	while (str[i] == '<' || str[i] == '>')
		i++;
	return (i);
}

size_t	skip_word(char *str, size_t i)
{
	while (str[i] != ' ' && str[i] && str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

size_t	redirlen(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[i + j] == '<' || str[i + j] == '>')
	{
		j = skip_redirection(str, j);
		j = skip_spaces(str, j);
		i = skip_word(str, j);
	}
	return (i);
}

size_t	argslen(char *str)
{
	return (skip_word(str, 0));
}
