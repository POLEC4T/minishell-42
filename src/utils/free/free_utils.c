/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/28 15:58:29 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_free_redirects(t_redirect **redirects)
// {
// 	int	i;

// 	if (!redirects)
// 		return ;
// 	i = 0;
// 	while (redirects[i])
// 	{
// 		if (redirects[i]->redir_type == HEREDOC)
// 			unlink(redirects[i]->filename);
// 		if (redirects[i]->filename != NULL)
// 			free(redirects[i]->filename);
// 		free(redirects[i]);
// 		i++;
// 	}
// 	free(redirects);
// }

// void	ft_free_cmd_content(void *content)
// {
// 	t_cmd	*cmd;

// 	if (!content)
// 		return ;
// 	cmd = cast_to_cmd(content);
// 	if (cmd->args != NULL)
// 		ft_free_tab((void **)cmd->args);
// 	if (cmd->redirects != NULL)
// 		ft_free_redirects(cmd->redirects);
// 	free(cmd);
// }

void	ft_free_redirects(t_context *ctx, t_redirect **redirects)
{
	int	i;

	if (!redirects)
		return ;
	i = 0;
	while (redirects[i])
	{
		if ((redirects[i]->redir_type == HEREDOC
				|| redirects[i]->redir_type == HEREDOC_NO_INTER)
			&& ctx->hd_pid > 0)
			unlink(redirects[i]->filename);
		if (redirects[i]->filename != NULL)
			free(redirects[i]->filename);
		free(redirects[i]);
		i++;
	}
	free(redirects);
}

void	ft_free_cmd_content_ctx(t_context *ctx, void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = cast_to_cmd(content);
	if (cmd->args != NULL)
		ft_free_tab((void **)cmd->args);
	if (cmd->redirects != NULL)
		ft_free_redirects(ctx, cmd->redirects);
	free(cmd);
}

void	ft_free_cmds_content_ctx(t_context *ctx)
{
	t_node	*curr;
	t_node	*next;

	curr = *ctx->head_cmd;
	while (curr)
	{
		next = curr->next;
		ft_free_cmd_content_ctx(ctx, curr->content);
		free(curr);
		curr = next;
	}
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
	if (context->head_cmd == NULL)
		return ;
	close_all_cmds_redirs(context->head_cmd);
	// if (*context->head_cmd)
	// 	ft_lstclear(context->head_cmd, ft_free_cmd_content);
	if (*context->head_cmd)
		ft_free_cmds_content_ctx(context);
	free(context->head_cmd);
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
