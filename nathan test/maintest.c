/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:47:13 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/11 16:55:10 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nathantest.h"

void	maintest(void)
{
	char *read;
	t_token *token_test;
	

	read = readline("pitishell >");
	token_test = parsing(read);
	printf("%s\n", token_test->data);
	exit(0);
}