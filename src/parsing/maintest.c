/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/23 18:17:01 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef enum
// {
// 	COMMAND,
// 	OPERATOR,
// 	PIPE,
// 	FLAG,
// 	ARGUMENT,
// 	FILES,
// 	IN,
// 	OUT,
// 	HEREDOC,
// 	DELIMITER,
// 	NUL
// }					token_type;

void	print_token_type(token_type type)
{
	switch (type)
	{
	case COMMAND:
		printf("COMMAND\n");
		break ;
	case OPERATOR:
		printf("OPERATOR\n");
		break ;
	case PIPE:
		printf("PIPE\n");
		break ;
	case FLAG:
		printf("FLAG\n");
		break ;
	case ARGUMENT:
		printf("ARGUMENT\n");
		break ;
	case FILES:
		printf("FILES\n");
		break ;
	case IN:
		printf("IN\n");
		break ;
	case OUT:
		printf("OUT\n");
		break ;
	case HEREDOC:
		printf("HEREDOC\n");
		break ;
	case DELIMITER:
		printf("DELIMITER\n");
		break ;
	default:
		printf("UNKNOWN TYPE\n");
		break ;
	}
}

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
			printf("Token Type: ");
			print_token_type(token->type);
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

t_node	*read_token(t_context ctx)
{
	char *read;
	t_node *token;

	(void)ctx;
	read = readline("pitishell >");

	if (read == NULL)
	{
		exit_free(&ctx);
	}
	read = quote_delimiter(read);
	token = parsing(read);
	// print_token_list(token);
	// free(read);
	// read = readline("pitishell >");

	return (token);
}