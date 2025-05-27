/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:23 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/27 15:58:37 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redirection(char *str, size_t *i)
{
	int	type;

	(*i)++;
	if (str[*i] == '>')
	{
		type = OUT_TRUNC;
		(*i)++;
	}
	else
	{
		type = OUT;
	}
	return (type);
}

int	handle_input_redirection(char *str, size_t *i)
{
	int	type;

	(*i)++;
	if (str[*i] == '<')
	{
		type = HEREDOC;
		(*i)++;
	}
	else
	{
		type = IN;
	}
	return (type);
}

int	detect_redirection_type(char *str, size_t *i)
{
	int	type;

	type = -1;
	if (str[*i] == '>')
	{
		type = handle_output_redirection(str, i);
	}
	else if (str[*i] == '<')
	{
		type = handle_input_redirection(str, i);
	}
	return (type);
}

size_t	extract_redirection_filename(char *str, char *filename)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	i = skip_spaces(str, i);
	while (str[i] && (str[i] != '>' && str[i] != '<'))
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (!quote && (str[i] == ' '))
			break ;
		else
			filename[j++] = str[i++];
	}
	filename[j] = '\0';
	return (i);
}

int	redirect_define(t_context *ctx, char *str, t_redirect **redir_addr)
{
	t_redirect	*redir;
	size_t		i;

	*redir_addr = malloc(sizeof(t_redirect));
	redir = *redir_addr;
	if (!redir)
		return (EXIT_FAILURE);
	i = 0;
	redir->redir_type = detect_redirection_type(str, &i);
	redir->fd_in = -2;
	redir->fd_out = -2;
	redir->filename = NULL;
	if (redir->redir_type == HEREDOC)
	{
		if (handle_heredoc(ctx, str, &i, redir_addr) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		redir->filename = malloc(redirlen(str) + 1);
		if (!redir->filename)
			return (EXIT_FAILURE);
		i += extract_redirection_filename(str + i, redir->filename);
	}
	return (EXIT_SUCCESS);
}
