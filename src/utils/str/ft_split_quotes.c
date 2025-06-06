/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:53:34 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/06 10:55:29 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_word(char **res, const char *s, t_split_ctx *ctx)
{
	int	old_i;
	int	start;

	old_i = ctx->i;
	while (s[ctx->i] && (ctx->quote || !is_char_in_str(s[ctx->i], ctx->delim)))
	{
		ctx->quote = update_quote_state(s[ctx->i], ctx->quote);
		ctx->i++;
	}
	start = old_i;
	if (start < ctx->i)
	{
		res[ctx->i_res] = malloc((ctx->i - start + 1) * sizeof(char));
		if (!res[ctx->i_res])
			return (0);
		fill_word(res[ctx->i_res], s + start, ctx->delim);
		ctx->i_res++;
	}
	return (1);
}

int	alloc_n_write(char **res, const char *s, char *delim)
{
	t_split_ctx	ctx;

	ctx.i = 0;
	ctx.i_res = 0;
	ctx.quote = 0;
	ctx.delim = delim;
	while (s[ctx.i])
	{
		while (s[ctx.i] && (is_char_in_str(s[ctx.i], delim) && !ctx.quote))
		{
			ctx.quote = update_quote_state(s[ctx.i], ctx.quote);
			ctx.i++;
		}
		if (!handle_word(res, s, &ctx))
			return (ctx.i_res);
	}
	return (-1);
}

char	**ft_split_quote(char const *s, char *delim)
{
	int nb_words;
	int i_alloc_res;
	char **res;

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