/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:56:30 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/14 10:24:35 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_define(char *str)
{
	char	*args;
	size_t	i;
	size_t	j;
	int		in_quotes;

	args = malloc(argslen(str) + 1);
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_quotes) // Début des guillemets
			in_quotes = 1;
		else if (str[i] == '"' && in_quotes) // Fin des guillemets
			in_quotes = 0;
		else if (!in_quotes && (str[i] == ' ' || str[i] == '<' || str[i] == '>')) // Hors des guillemets, arrêter
			break;
		else // Copier le caractère
		{
			args[j] = str[i];
			j++;
		}
		i++;
	}
	args[j] = '\0';
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

t_cmd	*cmd_initialize(size_t args_count, size_t redirects_count)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc((args_count + 1) * sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirects = malloc((redirects_count + 1) * sizeof(t_redirect *));
	if (!cmd->redirects)
	{
		free(cmd->args);
		free(cmd);
		return (NULL);
	}
	cmd->pid = -2;
	return (cmd);
}

t_cmd	*split_cmd(char *str)
{
	size_t	i;
	size_t	redirect;
	size_t	args;
	t_cmd	*cmd;

	i = 0;
	redirect = 0;
	args = 0;
	cmd = initialize_cmd_with_counts(str);
	if (!cmd)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			i = handle_redirection(str, i, cmd, &redirect);
		else if (str[i] != ' ')
			i = handle_argument(str, i, cmd, &args);
		else
			i++;
	}
	cmd->redirects[redirect] = NULL;
	cmd->args[count_args(str)] = NULL;
	return (cmd);
}
