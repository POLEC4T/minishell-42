/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/23 14:54:08 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirects(t_redirect **redirects)
{
	int	i;

	if (!redirects)
		return ;
	i = 0;
	while (redirects[i])
	{
		if (redirects[i]->redir_type == HEREDOC)
			unlink(redirects[i]->filename);
		if (redirects[i]->filename != NULL)
			free(redirects[i]->filename);
		free(redirects[i]);
		i++;
	}
	free(redirects);
}

void	ft_free_cmd_content(void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = cast_to_cmd(content);
	if (cmd->args != NULL)
		ft_free_tab((void **)cmd->args);
	if (cmd->redirects != NULL)
		ft_free_redirects(cmd->redirects);
	free(cmd);
}

void	free_exec(t_exec *data)
{
	if (data)
	{
		close_pipes(data);
		my_close(&data->saved_stdin);
		my_close(&data->saved_stdout);
		free(data);
	}
}

/**
 * @brief free each command in the ctx and close the file descriptors
 */
void	ft_free_ctx_cmds(t_context *context)
{
	t_node	**head_cmd;

	head_cmd = context->head_cmd;
	if (head_cmd == NULL)
		return ;
	close_all_cmds_redirs(head_cmd);
	if (*head_cmd)
		ft_lstclear(head_cmd, ft_free_cmd_content);
	free(head_cmd);
	context->head_cmd = NULL;
}

void	free_context(t_context *context)
{
	if (context->head_env != NULL)
	{
		ft_lstclear(context->head_env, ft_free_env_content);
		free(context->head_env);
	}
	ft_free_ctx_cmds(context);
	free_exec(context->exec_data);
}
