/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:31:32 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/06 10:28:50 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unescaped_quote(const char *str, int i, char quote,
		int in_other_quotes)
{
	return (str[i] == quote && !in_other_quotes && !(i > 0 && str[i
				- 1] == '\\'));
}

t_quote	init_quote(void)
{
	t_quote	init;

	init.dbl = 0;
	init.in_double = 0;
	init.in_single = 0;
	init.single = 0;
	return (init);
}

int	check_quotes_parity(const char *str)
{
	t_quote	quote;
	int		i;

	quote = init_quote();
	i = -1;
	while (str[++i])
	{
		if (is_unescaped_quote(str, i, '\'', quote.in_double))
		{
			quote.single++;
			quote.in_single = !quote.in_single;
		}
		else if (is_unescaped_quote(str, i, '"', quote.in_single))
		{
			quote.dbl++;
			quote.in_double = !quote.in_double;
		}
	}
	if (quote.single % 2 != 0 || quote.dbl % 2 != 0)
		return (-1);
	return (0);
}

static int	process_segment(const char **ptr, char *quote)
{
	const char	*seg_start;
	const char	*seg_end;

	*ptr = skip_leading_spaces(*ptr);
	if (**ptr == '\0')
		return (-1);
	seg_start = *ptr;
	*ptr = find_pipe(*ptr, quote);
	seg_end = *ptr - 1;
	seg_end = skip_trailing_spaces(seg_start, seg_end);
	if (is_segment_empty(seg_start, seg_end))
		return (-1);
	return (0);
}

int	pipe_check(const char *str)
{
	char		quote;
	const char	*ptr;

	ptr = str;
	quote = 0;
	while (1)
	{
		if (process_segment(&ptr, &quote) < 0)
			return (-1);
		if (*ptr == '|')
		{
			ptr++;
			if (*ptr == '\0')
				return (-1);
		}
		else
			break ;
	}
	if (quote)
		return (-1);
	return (0);
}
