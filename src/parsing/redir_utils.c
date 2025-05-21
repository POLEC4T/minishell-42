/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:23 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/21 13:03:17 by nle-gued         ###   ########.fr       */
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

	i = 0;
	j = 0;
	i = skip_spaces(str, i);
	if (str[i] == '"' || str[i] == '\'')
	{
		i++;
		while (str[i] == str[i - 1])
			i++;
	}
	while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'')
	{
		filename[j++] = str[i++];
	}
	filename[j] = '\0';
	return (i);
}

char	*get_incremented_hd_name(size_t hd_i)
{
	char	*str_hd_i;
	char	*hd_name;

	str_hd_i = ft_itoa(hd_i);
	if (!str_hd_i)
	{
		printf("hd todo");
		return (NULL);
	}
	hd_name = ft_strjoin(HD_FILENAME, str_hd_i);
	if (!hd_name)
	{
		printf("hd todo");
		return (NULL);
	}
	free(str_hd_i);
	return (hd_name);
}

char	*get_hd_name(void)
{
	char	*hd_name;
	size_t	hd_i;

	hd_i = 0;
	hd_name = get_incremented_hd_name(hd_i);
	while (access(hd_name, F_OK) == 0)
	{
		free(hd_name);
		hd_name = get_incremented_hd_name(hd_i);
		hd_i++;
	}
	return (hd_name);
}

int	handle_heredoc(char *str, size_t *i, t_redirect *redir)
{
	int		fd;
	char	*line;
	char	*eof;

	redir->filename = get_hd_name();
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	eof = malloc(redirlen(str) + 1);
	if (!eof)
		return (-1);
	*i += extract_redirection_filename(str + *i, eof);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(line);
	free(eof);
	return (0);
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
	if (redir->redir_type == HEREDOC)
	{
		if (handle_heredoc(str, &i, redir) == -1)
		{
			free(redir);
			return (NULL);
		}
	}
	else
	{
		redir->filename = malloc(redirlen(str) + 1);
		if (!redir->filename)
		{
			free(redir);
			return (NULL);
		}
		i += extract_redirection_filename(str + i, redir->filename);
	}
	redir->fd_in = -2;
	redir->fd_out = -2;
	return (redir);
}
