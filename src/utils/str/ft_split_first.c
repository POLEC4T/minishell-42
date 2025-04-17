/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 14:11:50 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_nb_words(char const *s, char *delim)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	if (is_char_in_str(s[i], delim))
		return (1);
	i++;
	while (s[i])
	{
		if (is_char_in_str(s[i], delim))
			return (2);
		i++;
	}
	return (1);
}

static char	*fill_word(char *word, char const *s, char *delim)
{
	int	i;

	i = 0;
	while (s[i] && !is_char_in_str(s[i], delim))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	*fill_rest(const char *s)
{
	int		len;
	char	*r;
	int		i;

	len = 0;
	while (s[len])
		len++;
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	while (++i < len)
		r[i] = s[i];
	r[len] = '\0';
	return (r);
}

static int	alloc_n_write(char **res, char const *s, char *delim)
{
	int	i;
	int	i_res;

	i = 0;
	i_res = 0;
	while (s[i] && !is_char_in_str(s[i], delim))
		i++;
	if (i > 0)
	{
		res[i_res] = malloc(i + 1);
		if (!res[i_res])
			return (EXIT_FAILURE);
		fill_word(res[i_res], s, delim);
		i_res++;
	}
	if (s[i])
	{
		res[i_res] = fill_rest(s + i + 1);
		if (!res[i_res])
			return (EXIT_FAILURE);
		i_res++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief diff with split: only splits on the first occurrence of delim
 */
char	**ft_split_first(char const *s, char *delim)
{
	char	**res;
	int		nb_words;
	int		ret;

	if (!s)
		return (NULL);
	nb_words = calc_nb_words(s, delim);
	res = ft_calloc((nb_words + 1), sizeof(char *));
	if (!res)
		return (NULL);
	if (nb_words > 0)
	{
		ret = alloc_n_write(res, s, delim);
		if (ret == EXIT_FAILURE)
		{
			ft_free_tab((void *)res);
			return (NULL);
		}
	}
	res[nb_words] = NULL;
	return (res);
}

// int	main(void)
// {
// 	char **result;
// 	int i;
// 	char *str = "DOCKER_HOST=unix:///run/user/=103=416/docker.sock";
// 	// printf("nb words: %d\n", calc_nb_words(str, "="));

// 	result = ft_split_first(str, "=");
// 	if (!result)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return (1);
// 	}
// 	i = 0;
// 	printf("%s\n", result[0]);
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i + 1]);
// 		i++;
// 	}
// 	ft_free_tab((void *)result);
// 	return (0);
// }