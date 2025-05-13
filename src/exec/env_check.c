/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:43:43 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 10:40:21 by mniemaz          ###   ########.fr       */
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

static char	*safe_ft_strjoin(t_context *ctx, char *s1, char *s2, char *to_free)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		if (to_free)
			free(to_free);
		msg("ft_strjoin", ": ", strerror(errno), STDERR_FILENO);
		exit_free(ctx);
	}
	return (res);
}

char	*get_cmd_path(t_context *ctx, char *cmd)
{
	char	*curr_path;
	int		i;
	char	**paths;

	paths = get_paths(ctx);
	if (cmd && ft_strlen(cmd) > 0 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd = safe_ft_strjoin(ctx, "/", cmd, NULL);
	i = -1;
	while (paths && paths[++i])
	{
		curr_path = safe_ft_strjoin(ctx, paths[i], cmd, cmd);
		if (access(curr_path, X_OK) != -1)
		{
			free(cmd);
			ft_free_tab((void **)paths);
			return (curr_path);
		}
		free(curr_path);
	}
	ft_fprintf(STDERR_FILENO, "command not found: %s\n", cmd + 1);
	ctx->exit_code = 127;
	free(cmd);
	ft_free_tab((void **)paths);
	exit_free(ctx);
	return (NULL);
}
