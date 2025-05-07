/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:49:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 17:49:13 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cwd_error(char *to_free)
{
	ft_fprintf(STDERR_FILENO, "cd: %s\n", strerror(errno));
	free(to_free);
	return (EXIT_FAILURE);
}