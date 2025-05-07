/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:43:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 17:37:00 by mniemaz          ###   ########.fr       */
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
 * @brief only used by exit builtin cmd
 * @details A valid result is
 * "[+|-]<number between -9223372036854775808 and 9223372036854775807>"
 */
long long	ft_atoi_exit(const char *str_exit_code, int *error)
{
	int					sign;
	unsigned long long	result;
	int					i;

	sign = 1;
	result = 0;
	i = 0;
	while (str_exit_code[i] && is_space(str_exit_code[i]))
		i++;
	if (str_exit_code[i] == '-' || str_exit_code[i] == '+')
	{
		if (str_exit_code[i] == '-')
			sign = -1;
		i++;
	}
	while (str_exit_code[i] && ft_isdigit(str_exit_code[i]))
	{
		result = result * 10 + (str_exit_code[i] - '0');
		if (is_overflow(result, sign))
			*error = 1;
		i++;
	}
	if (!(*error))
		*error = !(ft_strlen((char *)str_exit_code) == i);
	return (sign * result);
}
