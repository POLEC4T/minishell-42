/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:57:45 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 16:57:51 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicates a string and exits the program if it fails.
 * @param err_title : error title to print if strdup fails
 */
char	*ft_secure_strdup(t_context *ctx, char *s, char *err_title)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = ft_strdup(s);
	if (!dup)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", err_title, strerror(errno));
		exit_free(ctx);
	}
	return (dup);
}