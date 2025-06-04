/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:09:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/03 17:43:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if the key is valid
 * @details:
 * - the first character must not be a digit
 * - the key must contain only alphanumeric characters and underscores
 * - the key must not be empty
 */
static int	ft_is_arg_valid(char *key)
{
	int	i;

	if (!key || ft_isdigit(key[0]))
		return (0);
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (i != 0);
}

/**
 * @brief get the key and value from the string param line
 * @returns a str tab of two elements, [key, value]
 */
static char	**get_key_value(t_context *ctx, char *line)
{
	char	**line_tab;

	line_tab = ft_split_first(line, "=");
	if (line_tab == NULL)
	{
		ft_fprintf(STDERR_FILENO, "export: %s\n", strerror(errno));
		ctx->exit_code = EXIT_FAILURE;
		exit_free(ctx);
	}
	return (line_tab);
}

/**
 * @brief diff with command "env": 
 * - prints "export " before the line
 * - prints the the line EVEN IF there is no value
 */
void	display_all_env(t_node **head)
{
	t_node		*curr_node;
	t_key_value	*env;

	if (!head)
		return ;
	curr_node = *head;
	while (curr_node)
	{
		env = cast_to_key_value(curr_node->content);
		if (env && env->key && env->value)
			printf("export %s=\"%s\"\n", env->key, env->value);
		else if (env && env->key && !env->value)
			printf("export %s\n", env->key);
		curr_node = curr_node->next;
	}
}

/**
 * @param args : [key[=value]]
 */
int	ft_export(t_context *ctx, char **args)
{
	char	**kv;
	int		i;
	int		exit_code;

	if (!args)
		return (EXIT_FAILURE);
	exit_code = EXIT_SUCCESS;
	if (args[0] == NULL)
		display_all_env(ctx->head_env);
	i = -1;
	while (args[++i])
	{
		if (!ft_is_arg_valid(args[i]))
		{
			ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n",
				args[i]);
			exit_code = EXIT_FAILURE;
			continue ;
		}
		kv = get_key_value(ctx, args[i]);
		create_or_set_env_var(ctx, kv);
		ft_free_tab((void **)kv);
	}
	return (exit_code);
}
