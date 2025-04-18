/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:31:32 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/18 13:36:26 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax(t_node *head)
{
	t_node *current = head;
	while (current->next->content)
		current = current->next;
	t_token *token = cast_to_token(current->content);
	if (token->type == HEREDOC)
		printf("pitishell: syntax error\n");
	if (token->type == OPERATOR)
		printf("pitishell: syntax error\n");
	if (token->type == PIPE)
		printf("pitishell: syntax error\n");
	return (0);
}