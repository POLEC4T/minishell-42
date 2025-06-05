/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:59 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 11:16:00 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_create_or_set_env_var(t_context *context, char **to_free)
{
	if (to_free)
		ft_free_tab((void **)to_free);
	ft_fprintf(STDERR_FILENO, "create_or_set_env_var: %s\n", strerror(errno));
	exit_free(context);
}

/**
 * @brief create a new env variable or set the value of an existing one
 * @param kv: kv[0] = key, kv[1] = value
 */
void	create_or_set_env_var(t_context *context, char **kv)
{
	t_node		*node;
	t_key_value	*existing_kv;

	if (!kv[0])
		return ;
	node = ft_get_env_node(context->head_env, kv[0]);
	if (node == NULL)
	{
		node = ft_envnew(kv[0], kv[1]);
		if (!node)
			err_create_or_set_env_var(context, kv);
		ft_lstadd_back(context->head_env, node);
	}
	else
	{
		if (!kv[1])
			return ;
		existing_kv = cast_to_key_value(node->content);
		if (existing_kv->value)
			free(existing_kv->value);
		existing_kv->value = ft_strdup(kv[1]);
		if (!existing_kv->value)
			err_create_or_set_env_var(context, NULL);
	}
}

/**
 * @returns a new node for the environment linked list
 */
t_node	*ft_envnew(char *key, char *value)
{
	t_node		*new;
	t_key_value	*content;

	content = malloc(sizeof(t_key_value));
	if (!content)
		return (NULL);
	content->key = ft_strdup(key);
	if (!content->key)
		return (return_free(content, NULL, NULL));
	if (!value)
		content->value = NULL;
	else
	{
		content->value = ft_strdup(value);
		if (!content->value)
			return (return_free(content->key, content, NULL));
	}
	new = ft_lstnew(content);
	if (!new)
		return (return_free(content->key, content->value, content));
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
char	*ft_get_env_val(t_context *ctx, char *key)
{
	t_node		*node;
	t_key_value	*kv;
	char		*dup;

	node = ft_get_env_node(ctx->head_env, key);
	if (!node)
		return (NULL);
	kv = cast_to_key_value(node->content);
	if (kv && kv->value)
	{
		dup = ft_strdup(kv->value);
		if (!dup)
		{
			ft_fprintf(STDERR_FILENO, "ft_get_env_val: %s\n", strerror(errno));
			exit_free(ctx);
		}
		return (dup);
	}
	return (NULL);
}
