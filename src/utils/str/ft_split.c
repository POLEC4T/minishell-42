/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:14:51 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/14 14:50:25 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

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
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (!(is_char_in_str(s[i], delim)) && ((is_char_in_str(s[i + 1], delim))
				|| s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static char	*fill_word(char *word, char const *s, char *delim)
{
	int	i;

	i = -1;
	while (s[++i] && !(is_char_in_str(s[i], delim)))
		word[i] = s[i];
	word[i] = '\0';
	return (word);
}

static int	alloc_n_write(char **res, char const *s, char *delim)
{
	int	i;
	int	old_i;
	int	i_res;

	i = 0;
	i_res = 0;
	while (s[i])
	{
		while (s[i] && (is_char_in_str(s[i], delim)))
			i++;
		old_i = i;
		while (s[i] && !(is_char_in_str(s[i], delim)))
			i++;
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

char	**ft_split(char const *s, char *delim)
{
	char	**res;
	int		nb_words;
	int		i_alloc_res;

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
