/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:31:32 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/04 15:22:45 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_quote
{
	int		single;
	int		dbl;
	int		in_single;
	int		in_double;
}			t_quote;

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

int	pipe_check(const char *str)
{
	const char	*ptr = str;
	const char	*segment_start;
	const char	*segment_end;
	char		quote = 0;

	while (1)
	{
		// Sauter les espaces initiaux
		while (*ptr && isspace((unsigned char)*ptr))
			ptr++;
		if (*ptr == '\0')
			return (-1);
		segment_start = ptr;

		// Avancer jusqu'au prochain | hors quotes ou fin de chaîne
		while (*ptr)
		{
			if (!quote && (*ptr == '\'' || *ptr == '"'))
				quote = *ptr;
			else if (quote && *ptr == quote)
				quote = 0;
			else if (!quote && *ptr == '|')
				break;
			ptr++;
		}
		segment_end = ptr - 1;
		// Retirer les espaces à la fin du segment
		while (segment_end >= segment_start
			&& isspace((unsigned char)*segment_end))
			segment_end--;
		if (segment_end < segment_start)
			return (-1);
		if (*ptr == '|')
		{
			ptr++; // Passer le pipe
			if (*ptr == '\0')
				return (-1);
		}
		else
			break ;
	}
	// Si on sort du while avec une quote ouverte -> erreur de syntaxe
	if (quote)
		return (-1);
	return (0);
}

int	brackets_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] && str[i] != '|')
			{
				if (str[i] != ' ')
					break ;
				i++;
			}
			if (str[i] == '|' || !str[i])
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	is_syntax_valid(char *str)
{
	if (check_quotes_parity(str) != 0)
	{
		ft_fprintf(STDERR_FILENO, "syntax: quote parity issue\n");
		return (0);
	}
	if (strchr(str, '|') && pipe_check(str) != 0)
	{
		ft_fprintf(STDERR_FILENO, "syntax: pipe issue\n");
		return (0);
	}
	if (brackets_check(str) != 0)
	{
		ft_fprintf(STDERR_FILENO, "syntax: angle bracket issue\n");
		return (0);
	}
	return(1);
}

