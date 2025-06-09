/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <nle-gued@student.42lyon.fr>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/06 04:05:37 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 04:05:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_syntax_valid(t_context *ctx, char *str)
{
	if (check_quotes_parity(str) != 0)
	{
		ctx->exit_code = 2;
		ft_dprintf(STDERR_FILENO, "syntax: quote parity issue\n");
		return (0);
	}
	if (ft_strchr(str, '|') && pipe_check(str) != 0)
	{
		ctx->exit_code = 2;
		ft_dprintf(STDERR_FILENO, "syntax: pipe issue\n");
		return (0);
	}
	if (brackets_check(str) != 0)
	{
		ctx->exit_code = 2;
		ft_dprintf(STDERR_FILENO, "syntax: angle bracket issue\n");
		return (0);
	}
	return (1);
}
