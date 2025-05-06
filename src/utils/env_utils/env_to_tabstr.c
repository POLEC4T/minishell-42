/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tabstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:33:35 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/24 17:43:57 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_tabstr(t_node **head_env)
{
	char **res;

	if (!head_env)
		return (NULL);
	res = malloc((ft_lstsize(*head_env) + 1) * sizeof(char *));

	t_node *curr_node;
    t_key_value *curr_kv;
    
    curr_node = *head_env;
    int i = 0;
    char *tmp;
    while(curr_node)
    {
        curr_kv = cast_to_key_value(curr_node->content);

        tmp = ft_strjoin(curr_kv->key, "=");
        if (!tmp)
            printf("TODO");
        res[i] = ft_strjoin(tmp, curr_kv->value);
        free(tmp);
        if (!res[i])
            printf("TODO");
        curr_node = curr_node->next;
        i++;
    }
    res[i] = NULL;
    return (res);
}