/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/05 14:42:38 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_content(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = cast_to_token(content);
	if (token->data != NULL)
		free(token->data);
	free(token);
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
		ft_free_tab((void **)cmd->redirects);
	// my_close(&cmd->fd_in);
	// my_close(&cmd->fd_out);
	free(cmd);
}
void	free_exec(t_exec *data)
{
	if (data)
	{
		close_pipes(data);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		if (data->paths != NULL)
			ft_free_tab((void **)data->paths);
		free(data);
	}
}

void ft_free_ctx_cmds(t_node **head_cmd)
{
	if (!head_cmd)
		return ;
	ft_lstclear(head_cmd, ft_free_cmd_content);
	free(head_cmd);
}


void free_context(t_context *context)
{
	if (context->head_env)
		ft_lstclear(context->head_env, ft_free_env_content);
	if (context->head_env)
		free(context->head_env);
	ft_free_ctx_cmds(context->head_cmd);
	free_exec(context->exec_data);
}

void	exit_free(t_context *context)
{
	free_context(context);
	exit(context->exit_code);
}