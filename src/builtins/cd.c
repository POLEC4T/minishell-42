/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:01:44 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/18 16:38:27 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @if args is NULL, it returns EXIT_FAILURE
 * @if no args after "cd", it sets newpwd to the value of the HOME env
 * variable
 * @else, it sets newpwd to the value of args[1]
 */
static int	init_newpwd(t_context *context, char **args, char **newpwd)
{
	if (!args)
		return (EXIT_FAILURE);
	if (args[1] == NULL)
	{
		*newpwd = ft_get_env_val(context->head_env, "HOME");
		if (*newpwd == NULL)
		{
			ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		*newpwd = ft_strdup_null(args[1]);
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
	*newpwd = ft_get_env_val(context->head_env, "OLDPWD");
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
static int	prefix_home_to_pwd(t_context *context, char **newpwd)
{
	char	*home;
	char	*temp;

	home = ft_get_env_val(context->head_env, "HOME");
	if (home == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		free(*newpwd);
		return (EXIT_FAILURE);
	}
	temp = ft_strjoin(home, *newpwd + 1);
	if (!temp)
	{
		free(home);
		ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
		free(*newpwd);
		return (EXIT_FAILURE);
	}
	free(*newpwd);
	*newpwd = temp;
	free(home);
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the PWD and OLDPWD environment variables.
 */
static int	set_pwds(t_context *context, char **newpwd)
{
	char	*oldpwd;

	oldpwd = ft_get_env_val(context->head_env, "PWD");
	if (oldpwd == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: PWD not set\n");
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
	ft_set_env_val(context->head_env, "PWD", *newpwd);
	ft_set_env_val(context->head_env, "OLDPWD", oldpwd);
	free(*newpwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}

void	cd(t_context *context, char **args)
{
	char	*newpwd;

	newpwd = NULL;
	if (init_newpwd(context, args, &newpwd) == EXIT_FAILURE)
		return ;
	if (ft_strncmp(newpwd, "-", 2) == 0)
	{
		if (set_to_oldpwd(context, &newpwd) == EXIT_FAILURE)
			return ;
	}
	else if (newpwd[0] == '~')
	{
		if (prefix_home_to_pwd(context, &newpwd) == EXIT_FAILURE)
			return ;
	}
	set_pwds(context, &newpwd);
}
