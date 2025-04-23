/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:27:41 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/23 18:05:20 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_token_content(void *content)
{
    t_token *token;

    if (!content)
        return ;
    token = cast_to_token(content);
    if (token->data != NULL)
        free(token->data);
    free(token);
}

// void	free_token_list(t_node *head)
// {
// 	t_node	*current;
// 	t_node	*next_node;
// 	t_token	*token;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		next_node = current->next;
// 		if (current->content != NULL)
// 		{
// 			token = cast_to_token(current->content);
// 			if (token->data != NULL)
// 			{
// 				free(token->data);
// 			}
// 			free(token);
// 		}
// 		free(current);
// 		current = next_node;
// 	}
// }

void    exit_free(t_context *context)
{
    if (context->head_env)
        ft_lstclear(context->head_env, ft_free_env_content);
    if (context->head_env)
        free(context->head_env);
    if (context->head_token)
        ft_lstclear(&context->head_token, ft_free_token_content);
    exit(context->exit_code);
}