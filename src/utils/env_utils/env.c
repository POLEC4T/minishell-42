/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:59 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/23 14:34:45 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief create a new env variable or set the value of an existing one
 * @param kv: kv[0] = key, kv[1] = value
 */
void	create_or_set_env_var(t_context *context, char **kv)
{
	t_node		*node;
	t_key_value	*existing_kv;
	char		*old_value;

	if (!kv[0])
		return ;
	node = ft_get_env_node(context->head_env, kv[0]);
	if (node == NULL)
	{
		node = ft_envnew(kv[0], kv[1]);
		if (!node)
		{
			ft_free_tab((void **)kv);
			ft_fprintf(STDERR_FILENO, "create_or_set_env_var: %s\n",
				strerror(errno));
			exit_free(context);
		}
		ft_lstadd_back(context->head_env, node);
	}
	else
	{
		existing_kv = cast_to_key_value(node->content);
		old_value = existing_kv->value;
		if (old_value != NULL)
			free(old_value);
		existing_kv->value = ft_strdup(kv[1]);
	}
	ft_free_tab((void **)kv);
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
	new = ft_lstnew(content); // idee : mettre ca au debut de la fonction
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
		// TODO: why + 1 + 1 ???
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

void	print_env_val(t_context *ctx, char *key)
{
	char	*value;

	value = ft_get_env_val(ctx, key);
	if (value)
	{
		printf("%s\n", value);
		free(value);
	}
}

void	ft_free_env_content(void *content)
{
	t_key_value	*kv;

	if (!content)
		return ;
	kv = cast_to_key_value(content);
	free(kv->key);
	free(kv->value);
	free(kv);
}
