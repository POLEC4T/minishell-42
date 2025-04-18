/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/18 15:57:09 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *str)
{
	size_t	i;
	size_t	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 == 1)
		return (1);
	return (0);
}

int	check_last_pipe(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] != ' ')
			break ;
		i--;
	}
	if (str[i] == '|')
		return (1);
	return (0);
}

char	*quote_delimiter(char *str)
{
	char *to_add = calloc(1, 2);
	char *read;

	if (quote_count(str) != 0)
	{
        while (ft_strchr(to_add, '"') == 0)
		{
            read = readline(">");
			to_add = ft_strjoin(to_add, read);
		}
		str = ft_strjoin(str, to_add);
		return (quote_delimiter(str));
	}
    else if (check_last_pipe(str) != 0)
    {
        read = readline(">");
        str = ft_strjoin(str, read);
        return(quote_delimiter(str));
    }
    return(str);
}