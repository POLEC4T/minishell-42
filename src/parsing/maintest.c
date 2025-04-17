/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 16:53:00 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_node *head)
{
	t_node	*current;
	t_token	*token;

	current = head;
	while (current)
	{
		if (current->content) // ✅ protection contre les content NULL
		{
			token = cast_to_token(current->content);
			printf("Current Token Data: %s\n", token->data);
			printf("Token Type: %d\n", token->type);
		}
		else
		{
			printf("Current Token Data: NULL (content is NULL)\n");
		}
		if (current->prev && current->prev->content)
		{
			printf("Previous Token Data: %s\n",
				cast_to_token(current->prev->content)->data);
		}
		else
		{
			printf("Previous Token Data: NULL\n");
		}
		printf("----------\n");
		current = current->next;
	}
}

void	maintest(void)
{
	char *read;
	t_node *token;

	read = readline("pitishell >");
	while (read)
	{
		if (read == NULL)
		exit(42);
		token = parsing(read);
		
		print_token_list(token);
		read = readline("pitishell >");
	}
	exit(0);
}