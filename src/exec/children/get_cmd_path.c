/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:43:43 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 13:24:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_context *ctx)
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
			ft_dprintf(STDERR_FILENO, "get_paths: %s\n", strerror(errno));
			ctx->exit_code = EXIT_FAILURE;
			exit_free(ctx);
		}
		return (res);
	}
	return (NULL);
}

static int	is_directory(t_context *ctx, char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		ctx->exit_code = 127;
		ft_dprintf(STDERR_FILENO, "%s: %s\n", path, strerror(errno));
		exit_free(ctx);
	}
	return (S_ISDIR(st.st_mode));
}

static char	*find_cmd_in_path(t_context *ctx, char *cmd, char **paths)
{
	char	*curr_path;
	int		i;

	i = -1;
	if (paths == NULL)
		return (NULL);
	if (cmd[0] == '\0')
	{
		ctx->exit_code = 127;
		ft_free_tab((void **)paths);
		return (NULL);
	}
	while (paths[++i])
	{
		curr_path = safe_ft_double_strjoin(ctx, paths[i], "/", cmd);
		if (access(curr_path, X_OK) == 0)
		{
			ft_free_tab((void **)paths);
			return (curr_path);
		}
		free(curr_path);
	}
	ctx->exit_code = 127;
	ft_free_tab((void **)paths);
	return (NULL);
}

/**
 * @returns the absolute path of the command if
 * - it is not a directory
 * - it exists
 * - it is executable
 */
static char	*get_absolute_cmd_path(t_context *ctx, char *absolute_cmd,
		char **paths)
{
	if (paths != NULL)
		ft_free_tab((void **)paths);
	if (is_directory(ctx, absolute_cmd))
	{
		ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", absolute_cmd);
		ctx->exit_code = 126;
		exit_free(ctx);
	}
	if (access(absolute_cmd, X_OK) == 0)
		return (ft_secure_strdup(ctx, absolute_cmd, "get_absolute_cmd_path"));
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", absolute_cmd, strerror(errno));
		ctx->exit_code = 126;
		exit_free(ctx);
	}
	return (NULL);
}

char	*get_cmd_path(t_context *ctx, char *cmd)
{
	char	**paths;

	if (!cmd)
		return (NULL);
	paths = get_paths(ctx);
	if (paths == NULL || is_char_in_str('/', cmd))
		return (get_absolute_cmd_path(ctx, cmd, paths));
	else
		return (find_cmd_in_path(ctx, cmd, paths));
}
