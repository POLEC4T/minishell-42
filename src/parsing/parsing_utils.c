/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:55:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/09 09:57:51 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_spaces(char *str, size_t i)
{
	while (ft_isblank(str[i]) == 1 && str[i])
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
	char	in_quotes;

	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == in_quotes && in_quotes)
			in_quotes = 0;
		else if ((str[i] == '"' || str[i] == '\'') && !in_quotes)
			in_quotes = str[i];
		if (!in_quotes && (ft_isblank(str[i]) == 1 || str[i] == '<'
				|| str[i] == '>'))
			break ;
		else
			i++;
	}
	return (i);
}

size_t	redir_word_len(char *str)
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

size_t	get_arg_len(char *str)
{
	return (skip_word(str, 0));
}
