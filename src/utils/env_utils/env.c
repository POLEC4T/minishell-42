/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:59 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 18:07:18 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(t_context *ctx, char **envp)
{
    
    t_node *curr_node;
    int i;
    char **line;
    // char *key;
    char *value;

    i = -1;
    while (envp && envp[++i])
    {
        line = ft_split_first(envp[i], "=");
        if (!line)
        {
            // TODO
            
            continue ;
        }
        if (!line[0])
        {
            continue;
        }
        if (!line[1])
            value = NULL;
        else
            value = line[1];
        curr_node = ft_envnew(line[0], value);
        if (!curr_node)
        {
            continue;
        }
        ft_lstadd_back(ctx->head_env, curr_node);
        ft_free_tab((void **)line);
    }
}

/**
 * @returns a new node for the environment linked list
 */
t_node	*ft_envnew(char *key, char *value)
{
	t_node		*new;
	t_key_value	*content;

	if (!key)
		return (NULL);
	content = malloc(sizeof(t_key_value));
	if (!content)
		return (NULL);
	content->key = ft_strdup_null(key);
	if (!content->key)
	{
		free(content);
		return (NULL);
	}
	content->value = ft_strdup_null(value);
	if (!content->value)
	{
		free(content->key);
		free(content);
		return (NULL);
	}
	new = ft_lstnew(content);
	if (!new)
	{
		free(content->value);
		free(content->key);
		free(content);
		return (NULL);
	}
	return (new);
}

/**
 * @returns the node in the list that matches the key
 */
t_node	*ft_get_env(t_node **head, char *key)
{
	t_node		*tmp;
	t_key_value	*kv;

	if (!key || !head)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		kv = cast_to_key_value(tmp->content);
		if (ft_strncmp(kv->key, key, (size_t)ft_strlen(key) + 1 + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief edits the value of the node in the list that matches the key
 */
int	ft_edit_env_val(t_node **head, char *key, char *value)
{
	t_node		*tmp;
	t_key_value	*kv;

	if (!key || !head)
		return (EXIT_SUCCESS);
	tmp = *head;
	while (tmp)
	{
		kv = cast_to_key_value(tmp->content);
		if (ft_strncmp(kv->key, key, (size_t)ft_strlen(key) + 1 + 1) == 0)
		{
			free(kv->value);
			kv->value = ft_strdup_null(value);
			if (!kv->value)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_free_env_content(void *content)
{
	t_key_value *kv;

	if (!content)
		return ;
	kv = cast_to_key_value(content);
	free(kv->key);
	free(kv->value);
	free(kv);
}