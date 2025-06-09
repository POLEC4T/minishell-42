/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:36:28 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 09:41:38 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*err_set_arg(void)
{
	ft_fprintf(STDERR_FILENO, "set_arg: %s\n", strerror(errno));
	return (NULL);
}

char	*set_arg(char *str)
{
	char	*args;
	size_t	i;
	size_t	j;
	char	in_quotes;

	args = ft_calloc(get_arg_len(str) + 1, sizeof(char));
	if (!args)
		return (err_set_arg());
	i = -1;
	j = 0;
	in_quotes = 0;
	while (str[++i])
	{
		if (str[i] == in_quotes)
			in_quotes = 0;
		else if ((str[i] == '"' || str[i] == '\'') && !in_quotes)
			in_quotes = str[i];
		else if (!in_quotes && (ft_isblank(str[i]) == 1 || str[i] == '<'
				|| str[i] == '>'))
			break ;
		else
			args[j++] = str[i];
	}
	args[j] = '\0';
	return (args);
}

static int	err_set_cmd_node_content(void)
{
	ft_fprintf(STDERR_FILENO, "init_cmd: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}

int	set_cmd_node_content(char *str, t_context *ctx, t_node *cmd_node)
{
	size_t	i;
	size_t	i_args;
	size_t	i_redir;
	t_cmd	*cmd;

	i = 0;
	i_args = 0;
	i_redir = 0;
	cmd = init_cmd(str);
	if (!cmd)
		return (err_set_cmd_node_content());
	cmd_node->content = cmd;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			i = handle_redirection(ctx, &(t_str_index){.i = i, .str = str}, cmd,
					&i_redir);
		else if (ft_isblank(str[i]) != 1 && str[i] != ';' && str[i] != '\\')
			i = handle_argument(str, i, cmd, &i_args);
		else
			i++;
		if ((int)i == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
