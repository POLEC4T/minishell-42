/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:09:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/22 16:53:50 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_key_valid(char *key)
{
	int	i;

	if (!key || ft_isdigit(key[0]))
		return (0);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_key_value	*get_key_value(char *line)
{
	t_key_value	*kv;
	char		**line_tab;

	kv = malloc(sizeof(t_key_value));
	if (!kv)
		return (NULL);
	line_tab = ft_split_first(line, "=");
	if (!line_tab)
	{
		free(kv);
		return (NULL);
	}
	if (!line_tab[0])
	{
		free(kv);
		free(line_tab);
		return (NULL);
	}
	kv->key = ft_strdup(line_tab[0]);
	kv->value = ft_strdup(line_tab[1]);
	ft_free_tab((void **)line_tab);
	return (kv);
}

/**
 * @param args : [key[=value]]
 */
void	ft_export(t_context *ctx, char **args)
{
	t_key_value	*kv;
	int			i;
	int			exit_code;

	if (!args)
		return ;
	exit_code = 0;
	i = -1;
	while (args[++i])
	{
		kv = get_key_value(args[i]);
		if (!kv)
			continue ;
		if (!ft_is_key_valid(kv->key))
		{
			ft_fprintf(STDERR_FILENO,
				"export: `%s=%s': not a valid identifier\n", kv->key,
				kv->value);
			ft_free_env_content((void *)kv);
			exit_code = 1;
			continue ;
		}
		create_or_set_env_var(ctx, kv->key, kv->value);
		ft_free_env_content((void *)kv);
	}
}
