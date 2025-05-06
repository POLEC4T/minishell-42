/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/06 11:50:38 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_node **parsing(char *str)
{
    size_t i = 0;
    t_node **head_cmd = NULL;
    t_node *prev_cmd = NULL;
    t_node *new_node = NULL;

    head_cmd = malloc(sizeof(t_node *));
    *head_cmd = NULL;
    char **spipe = ft_split(str, "|");
    if (!spipe)
        return NULL;
    
    while (spipe[i])
    {
        new_node = ft_lstnew((void *)split_cmd(spipe[i]));
        new_node->prev = prev_cmd;
        if (prev_cmd)
            prev_cmd->next = new_node;
        prev_cmd = new_node;
        if (!*head_cmd)
        {
            *head_cmd = new_node;
        }


        i++;
    }
    ft_free_tab((void **)spipe);
    return (head_cmd);
}

