/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:38:11 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/11 16:24:23 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nathantest.h"

size_t	strcount(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		i++;
	return (i);
}

t_token	*put_data(char *str)
{
	size_t i;
	t_token *new_token;
	new_token = malloc(sizeof(t_token));

	i = 0;
	new_token->data = malloc((strcount(str) + 1 )* sizeof(char));
	while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
	{
		new_token->data[i] = str[i];
        i++;
	}
	new_token->data[i] = '\0';
    return(new_token);
}