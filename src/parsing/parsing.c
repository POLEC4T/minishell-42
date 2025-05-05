/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:51:33 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/05 12:03:12 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void display_cmd(t_node *node)
{
    size_t i;

    if (!node)
    {
        printf("Node is NULL.\n");
        return;
    }

    // Cast du content de t_node en t_cmd
    t_cmd *cmd = (t_cmd *)node->content;
    if (!cmd)
    {
        printf("Command structure is NULL.\n");
        return;
    }

    // Afficher les arguments
    printf("Arguments:\n");
    i = 0;
    while (cmd->args && cmd->args[i])
    {
        printf("  - %s\n", cmd->args[i]);
        i++;
    }

    // Afficher les redirections
    printf("Redirections:\n");
    i = 0;
    while (cmd->redirects && cmd->redirects[i])
    {
        printf("  - Filename: %s, Type: %d\n", 
            cmd->redirects[i]->filename, 
            cmd->redirects[i]->redir_type);
        i++;
    }

}
t_node **parsing(char *str)
{
    size_t i = 0;
    t_cmd *token_cmd;
    t_node **first_token = NULL;
    t_node *current_token = NULL;
    t_node *new_node = NULL;

    char **spipe = ft_split(str, "|");
    if (!spipe)
        return NULL;

    while (spipe[i])
    {
        new_node = malloc(sizeof(t_node));
        if (!new_node)
        {
  
            return NULL;
        }

        new_node->prev = current_token;
        new_node->next = NULL;
        new_node->content = NULL;
        token_cmd = split_cmd(spipe[i]);
        new_node->content = token_cmd;

        if (current_token)
            current_token->next = new_node;

        current_token = new_node;


        if (!first_token)
            first_token = &new_node;

        printf("Node %zu:\n", i);
        display_cmd(new_node);
        i++;
    }
    return first_token;
}

