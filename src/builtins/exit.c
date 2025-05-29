/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:43:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/29 19:35:34 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Format the exit code to be in the range of 0-255.
 */
static void	format_exit_code(t_context *context)
{
	int	code;

	code = context->exit_code;
	if (code < 0)
		code = 256 + code;
	else if (code > 255)
		code = code % 256;
	context->exit_code = code;
}

void	ft_exit(t_context *context, char **args)
{
	int	error;

	error = 0;
	if (ft_lstsize(*context->head_cmd) == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args && args[0])
	{
		context->exit_code = ft_atoi_exit(args[0], &error);
		if (error)
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				args[0]);
			context->exit_code = 2;
		}
		else if (args[1])
		{
			ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
			context->exit_code = 1;
			return ;
		}
	}
	format_exit_code(context);
	exit_free(context);
}
