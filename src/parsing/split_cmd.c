/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:56:30 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/13 11:01:08 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_redirect_core(char *str, size_t i, size_t redir)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i = skip_redirection(str, i);
			i = skip_spaces(str, i);
			i = skip_word(str, i);
			redir++;
		}
		else if (str[i] != ' ')
		{
			i = skip_word(str, i);
		}
		else
		{
			i++;
		}
	}
	return (redir);
}

size_t	count_args_core(char *str, size_t i, size_t args)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i = skip_redirection(str, i);
			i = skip_spaces(str, i);
			i = skip_word(str, i);
		}
		else if (str[i] != ' ')
		{
			i = skip_word(str, i);
			args++;
		}
		else
		{
			i++;
		}
	}
	return (args);
}

int	count_args(char *str)
{
	return ((int)count_args_core(str, 0, 0));
}

int	count_redirect(char *str)
{
	return ((int)count_redirect_core(str, 0, 0));
}

t_redirect	*redirect_define(char *str)
{
	t_redirect	*redir;
	size_t		i;
	size_t		j;
	size_t		filename_len;

	i = 0;
	j = 0;
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	filename_len = redirlen(str);
	redir->filename = malloc((filename_len + 1) * sizeof(char));
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
		{
			redir->redir_type = OUT_TRUNC;
			i++;
		}
		else
			redir->redir_type = OUT;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
		{
			redir->redir_type = HEREDOC;
			i++;
		}
		else
			redir->redir_type = IN;
	}
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		redir->filename[j] = str[i];
		i++;
		j++;
	}
	redir->filename[j] = '\0';
	redir->fd_in = -2;
	redir->fd_out = -2;
	return (redir);
}

char	*args_define(char *str)
{
	char	*args;
	size_t	i;

	i = 0;
	args = malloc(argslen(str) + 1);
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		args[i] = str[i];
		i++;
	}
	args[i] = '\0';
	return (args);
}

int	space_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}

t_cmd	*split_cmd(char *str)
{
	size_t	i;
	size_t	redirect;
	size_t	args;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = 0;
	redirect = 0;
	args = 0;
	cmd->args = malloc((count_args(str) + 1) * sizeof(char *));
	if (!cmd->args)
		return (NULL);
	cmd->redirects = malloc((count_redirect(str) + 1) * sizeof(t_redirect *));
	cmd->pid = -2;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			cmd->redirects[redirect] = redirect_define(str + i);
			redirect++;
			while (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] == ' ' && str[i])
				i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		if (str[i] != ' ')
		{
			cmd->args[args] = args_define(str + i);
			args++;
			while (str[i] != ' ' && str[i] && str[i] != '<' && str[i] != '>')
				i++;
		}
		else
			i++;
	}
	cmd->redirects[redirect] = NULL;
	cmd->args[args] = NULL;
	return (cmd);
}
