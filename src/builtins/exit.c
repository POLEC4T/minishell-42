/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:43:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 17:38:03 by mniemaz          ###   ########.fr       */
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

/**
 * @brief If there is only one command (not in a pipeline) -> exit
 * @details exit builtin cmd only exits the parent process if there is one cmd
 */
static void	exit_if_in_parent(t_context *context)
{
	if (ft_lstsize(*context->head_cmd) == 1)
	{
		printf("exit\n");
		exit_free(context);
	}
}

int	ft_exit(t_context *context, char **args)
{
	int	error;
	int	exit_code;

	error = 0;
	exit_code = 0;
	if (args && args[0])
	{
		if (args[1])
		{
			ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
			return (exit_code);
		}
		exit_code = ft_atoi_exit(args[0], &error);
		if (error)
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				args[0]);
			exit_code = 2;
		}
	}
	format_exit_code(context);
	exit_if_in_parent(context);
	return (exit_code);
}
