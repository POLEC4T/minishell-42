/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:59 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/22 17:07:16 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(t_context *ctx, char **envp)
{
    export(ctx, envp);
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
	content->key = ft_strdup(key);
	if (!content->key)
	{
		free(content);
		return (NULL);
	}
	if (!value)
		content->value = NULL;
	else
	{
		content->value = ft_strdup(value);
		if (!content->value)
		{
			free(content->key);
			free(content);
			return (NULL);
		}
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
t_node	*ft_get_env_node(t_node **head, char *key)
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
 * @returns the value of the node in the list that matches the key
 * @note needs to be freed
 */
char	*ft_get_env_val(t_node **head, char *key)
{
	t_node		*node;
	node = ft_get_env_node(head, key);
	if (!node)
		return (NULL);
	t_key_value	*kv;
	kv = cast_to_key_value(node->content);
	if (kv && kv->value)
		return (ft_strdup(kv->value));
	return (NULL);
}

/**
 * @brief sets the value of the node in the list that matches the key
 */
int	ft_set_env_val(t_node **head, char *key, char *value)
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
			kv->value = ft_strdup(value);
			if (!kv->value)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void print_env_val(t_node **head, char *key)
{
	char *value;
	value = ft_get_env_val(head, key);
	if (value)
	{
		printf("%s\n", value);
		free(value);
	}
	else
	{
		printf("%s not found\n", key);
	}
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