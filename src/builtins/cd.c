/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:01:44 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @if no path, it sets newpwd to the value of the HOME env
 * variable
 * @else, it sets newpwd to the value of path
 */
static int	init_newpwd(t_context *context, char *path, char **newpwd)
{
	if (path == NULL)
	{
		*newpwd = ft_get_env_val(context, "HOME");
		if (*newpwd == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		*newpwd = ft_strdup(path);
		if (*newpwd == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief sets newpwd to the env value of OLDPWD
 */
static int	set_to_oldpwd(t_context *context, char **newpwd)
{
	free(*newpwd);
	*newpwd = ft_get_env_val(context, "OLDPWD");
	if (*newpwd == NULL)
	{
		ft_dprintf(STDERR_FILENO, "cd: PWD not set\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", *newpwd);
	return (EXIT_SUCCESS);
}

static void	create_or_set_pwds_env(t_context *context, char *key, char *value)
{
	t_node		*node;
	t_key_value	*existing_kv;

	if (!key)
		return ;
	node = ft_get_env_node(context->head_env, key);
	if (node == NULL)
	{
		node = ft_envnew(key, value);
		if (!node)
		{
			ft_dprintf(STDERR_FILENO, "create_or_set_pwds_env: %s\n",
				strerror(errno));
			exit_free(context);
		}
		ft_lstadd_back(context->head_env, node);
	}
	else
	{
		existing_kv = cast_to_key_value(node->content);
		if (existing_kv->value != NULL)
			free(existing_kv->value);
		existing_kv->value = ft_strdup(value);
	}
}

/**
 * @brief 
 * - Chdir to the new pwd
 * - Create or set the PWD and OLDPWD environment variables.
 * 
 */
static int	set_pwds(t_context *ctx, char **newpwd)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (cwd_error(*newpwd));
	if (chdir(*newpwd) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", *newpwd, strerror(errno));
		free(*newpwd);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	free(*newpwd);
	*newpwd = getcwd(NULL, 0);
	if (*newpwd == NULL)
		return (cwd_error(oldpwd));
	create_or_set_pwds_env(ctx, "PWD", *newpwd);
	create_or_set_pwds_env(ctx, "OLDPWD", oldpwd);
	free(oldpwd);
	free(*newpwd);
	return (EXIT_SUCCESS);
}

/**
 * @param args : expected to be : [[path] NULL]
 */
int	ft_cd(t_context *context, char **args)
{
	char	*newpwd;

	if (!args)
		return (EXIT_FAILURE);
	if (ft_tablen((void **)args) > 1)
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	newpwd = NULL;
	if (init_newpwd(context, args[0], &newpwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strncmp(newpwd, "-", 2) == 0)
	{
		if (set_to_oldpwd(context, &newpwd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (set_pwds(context, &newpwd) == EXIT_FAILURE);
}
