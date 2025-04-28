/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/24 15:14:58 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_node *parsing(char *str)
{
    size_t i = 0;

    t_node *first_token = malloc(sizeof(t_node));
    if (!first_token)
        return NULL;

    t_node *current_token = first_token;
    first_token->prev = NULL;
    first_token->next = NULL;
    first_token->content = NULL; // ✅

    while (str[i])
    {
        if (str[i] == ' ')
        {
            i++;
        }
        else if (str[i] != '"')
        {
            put_exec(str + i, current_token, ' ');
            i += strcount(str + i, ' ');

            current_token->next = malloc(sizeof(t_node));
            if (!current_token->next)
                return first_token;

            current_token->next->prev = current_token;
            current_token = current_token->next;
            current_token->next = NULL;
            current_token->content = NULL; // ✅
        }
        else if (str[i] == '"' && str[i + 1] != '"')
        {
            i++;
            put_exec(str + i, current_token, '"');
            i += strcount(str + i, '"');
            i++;

            current_token->next = malloc(sizeof(t_node));
            if (!current_token->next)
                return first_token;

            current_token->next->prev = current_token;
            current_token = current_token->next;
            current_token->next = NULL;
            current_token->content = NULL; // ✅
        }
        else
        {
            i += 2;
        }
    }
    return first_token;
}

