/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:52:09 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/29 19:27:53 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	handle_redirection(t_context *ctx, char *str, size_t i, t_cmd *cmd)
{
	size_t	i_redir;

	i_redir = 0;
	if (redirect_define(ctx, str + i, &cmd->redirects[i_redir]) == EXIT_FAILURE)
		return (-1);
	i_redir++;
	i = skip_redirection(str, i);
	i = skip_spaces(str, i);
	i = skip_word(str, i);
	return (i);
}

// Gère les arguments dans la chaîne
size_t	handle_argument(char *str, size_t i, t_cmd *cmd, size_t *args)
{
	cmd->args[*args] = args_define(str + i);
	if (!cmd->args[*args])
		return (-1);
	(*args)++;
	i = skip_word(str, i);
	return (i);
}

// Initialise la structure t_cmd et retourne un pointeur
t_cmd	*initialize_cmd_with_counts(char *str)
{
	size_t	args_count;
	size_t	redirect_count;
	t_cmd	*cmd;

	args_count = count_args(str);
	redirect_count = count_redirect(str);
	cmd = init_cmd(args_count, redirect_count);
	return (cmd);
}
