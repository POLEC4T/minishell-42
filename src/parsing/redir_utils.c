/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:23 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 11:45:01 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redirection(char *str, size_t *i)
{
	int	type;

	(*i)++;
	if (str[*i] == '>')
	{
		type = OUT_TRUNC; // OUT_TRUNC
		(*i)++;
	}
	else
	{
		type = OUT; // OUT
	}
	return (type);
}

int	handle_input_redirection(char *str, size_t *i)
{
	int	type;

	(*i)++;
	if (str[*i] == '<')
	{
		type = 3; // HEREDOC
		(*i)++;
	}
	else
	{
		type = 4; // IN
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

	i = 0;
	j = 0;
	i = skip_spaces(str, i);
	while (str[i] && str[i] != ' ')
	{
		filename[j++] = str[i++];
	}
	filename[j] = '\0';
	return (i);
}

t_redirect	*redirect_define(char *str)
{
	t_redirect	*redir;
	size_t		i;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	i = 0;
	redir->redir_type = detect_redirection_type(str, &i);
	redir->filename = malloc(redirlen(str) + 1);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	i += extract_redirection_filename(str + i, redir->filename);
	redir->fd_in = -2;
	redir->fd_out = -2;
	return (redir);
}
