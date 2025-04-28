/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/28 18:43:56 by mniemaz          ###   ########.fr       */
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
	my_close(&cmd->fd_in);
	my_close(&cmd->fd_out);
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
		if (data->pids != NULL)
			free(data->pids);
		if (data->pipes != NULL)
			ft_free_tab((void **)data->pipes);
		free(data);
	}
}

void	exit_free(t_context *context)
{
	if (context->head_env)
		ft_lstclear(context->head_env, ft_free_env_content);
	if (context->head_env)
		free(context->head_env);
	if (context->head_token)
		ft_lstclear(&context->head_token, ft_free_token_content);
	if (context->head_cmd)
		ft_lstclear(context->head_cmd, ft_free_cmd_content);
	if (context->head_cmd)
		free(context->head_cmd);
    free_exec(context->exec_data);
	exit(context->exit_code);
}