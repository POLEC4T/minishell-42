/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/11 16:51:52 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nathantest.h"

t_token parsing(char *str)
{
    size_t i;
    i = 0;
    t_token first_token;
    t_token *current_token;
    
    first_token = *current_token;
    while(str[i])
    {
        if(str[i] == ' ')
        i++;
        else if (str[i] != '"')
        {
            current_token = put_data(str + i);
            i += strcount(str + i);
            current_token = current_token->next;
        }       
        else if(str[i] == '"' && str[i+1] != '"')
        {
            current_token = put_data(str + i);
            i += strcount(str + i);
            current_token = current_token->next;
        }
        else
            i += 2;
    }

    return(first_token);
}