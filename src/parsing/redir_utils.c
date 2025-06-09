/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:23 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/09 15:12:52 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_output_redir_type(char *str, size_t *i)
{
	int	type;

	(*i)++;
	if (str[*i] == '>')
	{
		type = OUT_TRUNC;
		(*i)++;
	}
	else
		type = OUT;
	return (type);
}

static t_redir_type	get_input_redir_type(char *str, size_t *i)
{
	int		type;
	size_t	j;

	(*i)++;
	if (str[*i] == '<')
	{
		(*i)++;
		j = skip_spaces(str, (*i));
		if (str[j] == '"' || str[j] == '\'')
			type = HEREDOC_NO_INTER;
		else
			type = HEREDOC;
	}
	else
		type = IN;
	return (type);
}

static t_redir_type	get_redir_type(char *str, size_t *i)
{
	int	redir_type;

	redir_type = UNDEFINED_INT;
	if (str[*i] == '>')
		redir_type = get_output_redir_type(str, i);
	else if (str[*i] == '<')
		redir_type = get_input_redir_type(str, i);
	return (redir_type);
}

static int	is_char_in_quotes(int index, const char *s)
{
	int	in_quote;

	in_quote = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		if (s[i] == '"' && (i == 0 || s[i - 1] != '\\'))
		{
			in_quote = !in_quote;
		}
		if (i == index)
		{
			return (in_quote);
		}
	}
	return (0);
}

/**
 * extracts the word after the redirection operator
 * @example: "ls > file.txt" -> "file.txt"
 * @example: "<< eof" -> "eof"
 * @returns the index of the next character after the redirection word
 */
size_t	extract_redir_word(char *str, char *filename)
{
	size_t	i;
	size_t	j;
	char	quote;

	j = 0;
	quote = 0;
	i = skip_spaces(str, 0);
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && is_char_in_quotes(i, str) == 0)
			break ;
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (!quote && (ft_isblank(str[i]) == 1))
			break ;
		else
			filename[j++] = str[i++];
	}
	filename[j] = '\0';
	return (i);
}

int	set_redir(t_context *ctx, char *str, t_redirect **redir)
{
	size_t	i;

	*redir = malloc(sizeof(t_redirect));
	if (!*redir)
		return (return_int_failure_msg("set_redir"));
	i = 0;
	(*redir)->redir_type = get_redir_type(str, &i);
	(*redir)->fd_in = UNDEFINED_INT;
	(*redir)->fd_out = UNDEFINED_INT;
	(*redir)->filename = NULL;
	if ((*redir)->redir_type == HEREDOC
		|| (*redir)->redir_type == HEREDOC_NO_INTER)
	{
		if (handle_hd(ctx, str, &i, redir) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		(*redir)->filename = malloc((redir_word_len(str) + 1) * sizeof(char));
		if (!(*redir)->filename)
			return (return_int_failure_msg("set_redir"));
		i += extract_redir_word(str + i, (*redir)->filename);
	}
	return (EXIT_SUCCESS);
}
