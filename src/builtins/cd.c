/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:01:44 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/05 17:10:59 by mniemaz          ###   ########.fr       */
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
			ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		*newpwd = ft_strdup(path);
		if (*newpwd == NULL)
		{
			ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
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
		ft_fprintf(STDERR_FILENO, "cd: PWD not set\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", *newpwd);
	return (EXIT_SUCCESS);
}

/**
 * @brief sets newpwd to the value of HOME concatenated with the rest of newpwd.
 */
static int	prefix_home_path(t_context *context, char **newpwd)
{
	char	*home;
	char	*temp;

	home = ft_get_env_val(context, "HOME");
	if (home == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		free(*newpwd);
		return (EXIT_FAILURE);
	}
	temp = ft_strjoin(home, *newpwd + 1);
	free(*newpwd);
	if (!temp)
	{
		free(home);
		ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	*newpwd = temp;
	free(home);
	return (EXIT_SUCCESS);
}

void create_or_set_env_var(t_context *context, char *key, char *value)
{
	t_node	*node;

	node = ft_get_env_node(context->head_env, key);
	if (node == NULL)
	{
		node = ft_envnew(key, value);
		ft_lstadd_back(context->head_env, node);
	}
	else
	{
		free(cast_to_key_value(node->content)->value);
		cast_to_key_value(node->content)->value = value;
	}
}

/**
 * @brief Set the PWD and OLDPWD environment variables.
 */
static int	set_pwds(t_context *context, char **newpwd)
{
	char	*oldpwd;
	// char	*to_free;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
		free(*newpwd);
		return (EXIT_FAILURE);
	}
	if (chdir(*newpwd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "cd: %s: %s\n", *newpwd, strerror(errno));
		free(*newpwd);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	free(*newpwd);
	*newpwd = getcwd(NULL, 0);
	if (*newpwd == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	// TODO clean this shhh
	// to_free = *newpwd;
	// *newpwd = ft_strjoin("PWD=", *newpwd);
	// if (!(*newpwd))
	// {
	// 	free(to_free);
	// 	free(oldpwd);
	// 	ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
	// 	return (EXIT_FAILURE);
	// }
	// free(to_free);
	// to_free = oldpwd;
	// oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	// if (!oldpwd)
	// {
	// 	free(to_free);
	// 	free(*newpwd);
	// 	ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
	// 	return (EXIT_FAILURE);
	// }
	// free(to_free);
	// ft_export(context, (char *[]){*newpwd, NULL});
	// ft_export(context, (char *[]){oldpwd, NULL});

	create_or_set_env_var(context, "PWD", *newpwd);
	create_or_set_env_var(context, "OLDPWD", oldpwd);
	free(*newpwd);
	free(oldpwd);
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
		ft_fprintf(STDERR_FILENO, "cd: too many arguments\n");
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
	else if (newpwd[0] == '~')
	{
		if (prefix_home_path(context, &newpwd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (set_pwds(context, &newpwd) == EXIT_FAILURE);
}
