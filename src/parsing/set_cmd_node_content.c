/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:36:28 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 13:39:09 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*err_args_define(void)
{
	ft_fprintf(STDERR_FILENO, "args_define: %s\n", strerror(errno));
	return (NULL);
}

char	*args_define(char *str)
{
	char	*args;
	size_t	i;
	size_t	j;
	char	in_quotes;

	args = malloc((argslen(str) + 1) * sizeof(char));
	if (!args)
		return (err_args_define());
	i = -1;
	j = 0;
	in_quotes = 0;
	while (str[++i])
	{
		if (str[i] == in_quotes)
			in_quotes = 0;
		else if ((str[i] == '"' || str[i] == '\'') && !in_quotes)
			in_quotes = str[i];
		else if (!in_quotes && (str[i] == ' ' || str[i] == '<'
				|| str[i] == '>'))
			break ;
		else
			args[j++] = str[i];
	}
	args[j] = '\0';
	return (args);
}

t_cmd	*init_cmd(size_t args_count, size_t redirects_count)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc((args_count + 1), sizeof(char *));
	if (!cmd->args)
		return (return_free(cmd, NULL, NULL));
	cmd->redirects = ft_calloc((redirects_count + 1), sizeof(t_redirect *));
	if (!cmd->redirects)
		return (return_free(cmd, NULL, NULL));
	cmd->pid = -2;
	cmd->exit_code = EXIT_SUCCESS;
	return (cmd);
}

static int	err_set_cmd_node_content(void)
{
	ft_fprintf(STDERR_FILENO, "init_cmd: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}

int	set_cmd_node_content(char *str, t_context *ctx, t_node *cmd_node)
{
	size_t	i;
	size_t	args;
	t_cmd	*cmd;
	size_t i_redir;

	i = 0;
	args = 0;
	i_redir = 0;
	cmd = initialize_cmd_with_counts(str);
	if (!cmd)
		return (err_set_cmd_node_content());
	cmd_node->content = (void *)cmd;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			i = handle_redirection(ctx, str, i, cmd, &i_redir);
		else if (str[i] != ' ' && str[i] != ';' && str[i] != '\\')
			i = handle_argument(str, i, cmd, &args);
		else
			i++;
		if ((int)i == -1)
			return (EXIT_FAILURE);
	}
	cmd->args[count_args(str)] = NULL;
	return (EXIT_SUCCESS);
}
