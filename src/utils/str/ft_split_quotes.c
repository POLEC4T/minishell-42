/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:53:34 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 12:53:35 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_char_in_str(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (c == s[i++])
			return (1);
	return (0);
}

/**
 * @brief Updates the quote state based on the current character.
 */
static char	update_quote_state(char current, char quote)
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

static void	free_tab(char **tab, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		free(tab[i]);
	free(tab);
}

static int	calc_nb_words(char const *s, char *delim)
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
		if (!quote && !is_char_in_str(s[i], delim) && ((is_char_in_str(s[i + 1],
						delim) && !update_quote_state(s[i + 1], quote)) || s[i
				+ 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static char	*fill_word(char *word, char const *s, char *delim)
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

static int	alloc_n_write(char **res, char const *s, char *delim)
{
	int		i;
	int		i_res;
	int		old_i;
	char	quote;

	i = 0;
	i_res = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && ((is_char_in_str(s[i], delim) && !quote)))
		{
			quote = update_quote_state(s[i], quote);
			i++;
		}
		old_i = i;
		while (s[i] && (quote || !is_char_in_str(s[i], delim)))
		{
			quote = update_quote_state(s[i], quote);
			i++;
		}
		if (old_i < i)
		{
			res[i_res] = malloc((i - old_i + 1) * sizeof(char));
			if (!res[i_res])
				return (i_res);
			fill_word(res[i_res], s + old_i, delim);
			i_res++;
		}
	}
	return (-1);
}

char	**ft_split_quote(char const *s, char *delim)
{
	char **res;
	int nb_words;
	int i_alloc_res;

	if (!s)
		return (NULL);
	nb_words = calc_nb_words(s, delim);
	res = malloc((nb_words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i_alloc_res = alloc_n_write(res, s, delim);
	if (i_alloc_res != -1)
	{
		free_tab(res, i_alloc_res);
		return (NULL);
	}
	res[nb_words] = NULL;
	return (res);
}