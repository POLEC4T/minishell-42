/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/16 14:26:15 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nathantest.h"

void	maintest(void)
{
	char *read;
	t_token *token;
	

	
	read = readline("pitishell >");
	token = parsing(read);
	while (token->next != NULL)
    {
        printf("interpretation : %d contenu  : %s\n", token->type, token->data);
        token = token->next;
    }

	exit(0);
}