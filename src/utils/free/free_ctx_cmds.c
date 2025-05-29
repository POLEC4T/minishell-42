/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:57:26 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 13:01:53 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirects(t_context *ctx, t_redirect **redirects)
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

static void	free_cmd_content_ctx(t_context *ctx, void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = cast_to_cmd(content);
	if (cmd->args != NULL)
		ft_free_tab((void **)cmd->args);
	if (cmd->redirects != NULL)
		free_redirects(ctx, cmd->redirects);
	free(cmd);
}

static void	free_cmds_content_ctx(t_context *ctx)
{
	t_node	*curr;
	t_node	*next;

	curr = *ctx->head_cmd;
	while (curr)
	{
		next = curr->next;
		free_cmd_content_ctx(ctx, curr->content);
		free(curr);
		curr = next;
	}
}

/**
 * @brief free each command in the ctx and close the file descriptors
 */
void	free_ctx_cmds(t_context *context)
{
	if (context->head_cmd == NULL)
		return ;
	close_all_cmds_redirs(context->head_cmd);
	if (*context->head_cmd)
		free_cmds_content_ctx(context);
	free(context->head_cmd);
	context->head_cmd = NULL;
}
