/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/12 17:33:34 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_node **head_cmd)
{
	t_node	*cmd;
	t_cmd	*cmd_content;

	cmd = *head_cmd;
	while (cmd)
	{
		cmd_content = cast_to_cmd(cmd->content);
		if (!cmd_content)
			break ;
		printf("Command: ");
		for (int i = 0; cmd_content->args && cmd_content->args[i]; i++)
			printf("%s ", cmd_content->args[i]);
		if (cmd_content->redirects)
		{
			for (int j = 0; cmd_content->redirects[j]; j++)
			{
				if (cmd_content->redirects[j]->redir_type == IN)
					printf("< ");
				else if (cmd_content->redirects[j]->redir_type == OUT)
					printf("> ");
				else if (cmd_content->redirects[j]->redir_type == HEREDOC)
					printf("<< ");
				else if (cmd_content->redirects[j]->redir_type == OUT_TRUNC)
					printf(">> ");
				printf("%s ", cmd_content->redirects[j]->filename);
			}
		}
		printf("\n");
		cmd = cmd->next;
	}
}

void	ft_exec(t_context *ctx)
{
	// print_cmds(ctx->head_cmd);
	init_exec(ctx);
	start_children(ctx);
	wait_children(ctx);
}
