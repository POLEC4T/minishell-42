/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:09:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/06 18:00:05 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : fix ft_is_key_valid
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

/**
 * @brief get the key and value from a char * line
 * @returns a str tab of two elements, [key, value]
 */
static char	**get_key_value(t_context *ctx, char *line)
{
	char	**line_tab;

	if (!line)
		return (NULL);
	line_tab = ft_split_first(line, "=");
	if (line_tab == NULL)
	{
		ft_fprintf(STDERR_FILENO, "export: %s\n", strerror(errno));
		exit_free(ctx);
	}
	return (line_tab);
}

static void	print_export_err(char *key, char *value)
{
	if (value != NULL)
		ft_fprintf(STDERR_FILENO, "export: `%s=%s': not a valid identifier\n",
			key, value);
	else
		ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", key,
			value);
}

/**
 * @param args : [key[=value]]
 */
void	ft_export(t_context *ctx, char **args)
{
	char	**kv;
	int		i;
	int		exit_code;

	if (!args)
		return ;
	exit_code = 0;
	i = -1;
	while (args[++i])
	{
		kv = get_key_value(ctx, args[i]);
		if (!kv)
			continue ;
		if (!ft_is_key_valid(kv[0]))
		{
			print_export_err(kv[0], kv[1]);
			ft_free_tab((void **)kv);
			exit_code = 1;
			continue ;
		}
		create_or_set_env_var(ctx, kv[0], kv[1]);
		ft_free_tab((void **)kv);
	}
}
