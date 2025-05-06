/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:43:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/06 16:27:38 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

static int	is_overflow(unsigned long long result, int sign)
{
	if (sign == 1 && result > LONG_MAX)
		return (1);
	if (sign == -1 && result > (unsigned long long)LONG_MAX + 1)
		return (1);
	return (0);
}
/**
 * @brief A valid str is
 * "[+|-]<number between -9223372036854775808 and 9223372036854775807>"
 */
static long long	ft_atoi_exit(const char *str, int *error)
{
	int					sign;
	unsigned long long	result;
	int					i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (is_overflow(result, sign))
			*error = 1;
		i++;
	}
	if (!(*error))
		*error = !(ft_strlen((char *)str) == i);
	return (sign * result);
}

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
