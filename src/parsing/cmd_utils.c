/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:52:09 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/06 10:26:04 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	handle_redirection(t_context *ctx, t_str_index *rl, t_cmd *cmd,
		size_t *i_redir)
{
	char	*str;
	size_t	i;

	str = rl->str;
	i = rl->i;
	if (set_redir(ctx, str + i, &cmd->redirects[*i_redir]) == EXIT_FAILURE)
		return (-1);
	(*i_redir)++;
	i = skip_redirection(str, i);
	i = skip_spaces(str, i);
	i = skip_word(str, i);
	return (i);
}

// Gère les arguments dans la chaîne
size_t	handle_argument(char *str, size_t i, t_cmd *cmd, size_t *args)
{
	cmd->args[*args] = set_arg(str + i);
	if (!cmd->args[*args])
		return (-1);
	(*args)++;
	i = skip_word(str, i);
	return (i);
}

// Initialise la structure t_cmd et retourne un pointeur
t_cmd	*init_cmd(char *str)
{
	size_t	nb_args;
	size_t	nb_redirect;
	t_cmd	*cmd;

	nb_args = count_args(str);
	nb_redirect = count_redirect(str);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc((nb_args + 1), sizeof(char *));
	if (!cmd->args)
		return (return_free(cmd, NULL, NULL));
	cmd->redirects = ft_calloc((nb_redirect + 1), sizeof(t_redirect *));
	if (!cmd->redirects)
		return (return_free(cmd, cmd->args, NULL));
	cmd->pid = UNDEFINED_INT;
	return (cmd);
}
