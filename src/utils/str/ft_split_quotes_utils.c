/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:36:53 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/06 11:09:49 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the quote state based on the current character.
 */
char	update_quote_state(char current, char quote)
{
	if ((current == '\'' || current == '\"'))
	{
		if (quote == 0)
			return (current);
		else if (quote == current)
			return (0);
	}
	return (quote);
}

int	calc_nb_words_quote(char const *s, char *delim)
{
	int		i;
	int		counter;
	char	quote;

	i = 0;
	counter = 0;
	quote = 0;
	while (s[i])
	{
		quote = update_quote_state(s[i], quote);
		if (!quote
			&& !is_char_in_str(s[i], delim)
			&& ((is_char_in_str(s[i + 1], delim)
					&& !update_quote_state(s[i + 1], quote))
				|| s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

char	*fill_word_quote(char *word, char const *s, char *delim)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		quote = update_quote_state(s[i], quote);
		if (!quote && is_char_in_str(s[i], delim))
			break ;
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
