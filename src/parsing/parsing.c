/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 14:01:42 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *parsing(char *str)
{
    size_t i = 0;


    t_token *first_token = malloc(sizeof(t_token));
    t_token *current_token = first_token;
    first_token->previous = NULL;

    if (!first_token)
        return NULL; 

    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else if (str[i] != '"')
        {
            put_data(str + i, current_token, ' ');
            i += strcount(str + i, ' ');

            current_token->next = malloc(sizeof(t_token));
            
            if (!current_token->next)
                return first_token; 
            
            current_token->next->previous = current_token ;
            current_token = current_token->next;
            current_token->next = NULL; 
        }
        else if (str[i] == '"' && str[i + 1] != '"')
        {
            i++;
            put_data(str + i, current_token, '"');
            i += strcount(str + i, '"');
            i++;

           
            current_token->next = malloc(sizeof(t_token));
            
            if (!current_token->next)
                return first_token; 
            
            current_token->next->previous = current_token ;    
            current_token = current_token->next;
            current_token->next = NULL; 
        }
        else
        {
            i += 2;
        }
    }
    return first_token;
}
