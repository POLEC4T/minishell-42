/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:43:43 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/14 13:53:56 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_context *ctx)
{
	char	**res;
	char	*path;

	path = ft_get_env_val(ctx, "PATH");
	if (path)
	{
		res = ft_split(path, ":");
		free(path);
		if (!res)
		{
			ft_fprintf(STDERR_FILENO, "get_paths: %s\n", strerror(errno));
			exit_free(ctx);
		}
		return (res);
	}
	return (NULL);
}

static char	*safe_ft_double_strjoin(t_context *ctx, char *s1, char *s2, char *s3)
{
	char	*res;

	res = ft_double_strjoin(s1, s2, s3);
	if (!res)
	{
		ft_fprintf(STDERR_FILENO, "safe_ft_strjoin: %s\n", strerror(errno));
		exit_free(ctx);
	}
	return (res);
}

/**
 * @returns the path of the command if it exists in PATH, else NULL
 */
char	*get_cmd_path(t_context *ctx, char *cmd)
{
	char	*curr_path;
	int		i;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (cmd && ft_strlen(cmd) > 0 && access(cmd, X_OK) != -1)
		return (cmd);
	paths = get_paths(ctx);
	i = -1;
	while (paths && paths[++i])
	{
		curr_path = safe_ft_double_strjoin(ctx, paths[i], "/", cmd);
		if (access(curr_path, X_OK) != -1)
		{
			ft_free_tab((void **)paths);
			return (curr_path);
		}
		free(curr_path);
	}
	ft_free_tab((void **)paths);
	return (NULL);
}
