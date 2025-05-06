/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/06 13:40:11 by mniemaz          ###   ########.fr       */
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
		free(data);
	}
}

/**
 * @brief free each command in the ctx and close the file descriptors
 */
void ft_free_ctx_cmds(t_context *context)
{
	t_node	**head_cmd;

	head_cmd = context->head_cmd;
	if (!head_cmd)
		return ;
	close_fds_cmds(head_cmd);
	if (*head_cmd)
		ft_lstclear(head_cmd, ft_free_cmd_content);
	free(head_cmd);
	context->head_cmd = NULL;
}

void free_context(t_context *context)
{
	if (context->head_env)
		ft_lstclear(context->head_env, ft_free_env_content);
	if (context->head_env)
		free(context->head_env);
	ft_free_ctx_cmds(context);
	free_exec(context->exec_data);
}

void	exit_free(t_context *context)
{
	free_context(context);
	exit(context->exit_code);
}