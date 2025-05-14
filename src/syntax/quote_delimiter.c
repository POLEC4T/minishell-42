/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/14 15:06:51 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *str, char quote)
{
	size_t	i;
	size_t	nbquote;
	char	outquote;

	if (quote == '"')
		outquote = '\'';
	else
		outquote = '"';
	i = 0;
	nbquote = 0;
	while (str[i])
	{
		if (str[i] == outquote)
		{
			i++;
			while (str[i] != outquote && str[i])
				i++;
		}
		if (str[i] == quote)
		{
			nbquote++;
			i++;
			while (str[i] != quote && str[i])
				i++;
			if (str[i] == quote)
				nbquote++;
		}
		i++;
	}
	return (nbquote % 2);
}

int	check_last_pipe(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] && str[i] != ' ')
			break ;
		i--;
	}
	if (str[i] && str[i] == '|')
		return (1);
	return (0);
}

char	find_last_quote(char *str)
{
	size_t	i;

	i = strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			break ;
		i--;
	}
	if (str[i] == '"')
		return ('\'');
	if (str[i] == '\'')
		return ('"');
	return (0);
}

char	*quote_delimiter(char *str)
{
	char	*to_add;
	char	*read;

	to_add = ft_calloc(1, 2);
	if ((quote_count(str, '"') != 0) && (quote_count(str, '\'') != 0))
	{
		while (ft_strchr(to_add, find_last_quote(str)) == 0)
		{
			read = readline(">");
			free(to_add);
			to_add = ft_strjoin(to_add, read);
		}
		str = ft_strjoin(str, to_add);
		return (quote_delimiter(str));
	}
	else if (quote_count(str, '"') != 0)
	{
		while (ft_strchr(to_add, '"') == 0)
		{
			read = readline(">");
			free(to_add);
			to_add = ft_strjoin(to_add, read);
		}
		str = ft_strjoin(str, to_add);
		return (quote_delimiter(str));
	}
	else if (quote_count(str, '\'') != 0)
	{
		while (ft_strchr(to_add, '\'') == 0)
		{
			read = readline(">");
			free(to_add);
			to_add = ft_strjoin(to_add, read);
		}
		str = ft_strjoin(str, to_add);
		return (quote_delimiter(str));
	}
	else if (ft_strchr(str, '|') && check_last_pipe(str) != 0)
	{
		read = readline(">");
		str = ft_strjoin(str, read);
		return (quote_delimiter(str));
	}
	free(to_add);
	return (str);
}
