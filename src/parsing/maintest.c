/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 13:59:32 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	print_token_list(t_token *head)
{
	t_token *current = head;

	while (current)
	{
		printf("Current Token Data: %s\n", current->data);
		printf("Token Type: %d\n", current->type); // vous pouvez adapter selon comment afficher le type
		if (current->previous)
			printf("Previous Token Data: %s\n", current->previous->data);
		else
			printf("Previous Token Data: NULL\n");
		printf("----------\n");
		current = current->next;
	}
}


void	maintest(void)
{
	char *read;
	t_token *token;
	

	
	read = readline("pitishell >");
	token = parsing(read);
	
	print_token_list(token);
	// while (token->next != NULL)
	// {
	//     printf("interpretation : %d contenu  : %s\n", token->type, token->data);
	//     token = token->next;
	// }
	
	exit(0);
}