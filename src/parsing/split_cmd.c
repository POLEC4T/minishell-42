/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:56:30 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/05 11:40:46 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *str)
{
	size_t	i;
	size_t	args;

	i = 0;
	args = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] == ' ' && str[i])
				i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
				i++;
			args++;
		}
		else
			i++;
	}
	return (args);
}

int	count_redirect(char *str)
{
	size_t	i;
	size_t	redir;

	i = 0;
	redir = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] == ' ' && str[i])
				i++;
			while (str[i] != ' ' && str[i])
				i++;
			redir++;
		}
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
				i++;
		}
		else
			i++;
	}
	return (redir);
}
int	redirlen(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[i + j] == '<' || str[i + j] == '>')
	{
		while (str[i + j] == '<' || str[i + j] == '>')
			j++;
		while (str[i + j] == ' ' && str[i + j])
			j++;
		while (str[i + j] != ' ' && str[i + j])
			i++;
	}
	return (i);
}
int	argslen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != ' ' && str[i] && str[i] != '<' && str[i] != '>')
		i++;
	return (i);
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
	cmd->redirects = malloc(count_redirect(str) * sizeof(t_redirect *));
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
