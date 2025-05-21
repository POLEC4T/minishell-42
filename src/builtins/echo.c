/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:48:01 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/21 11:42:42 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @returns the number of -n options in args (can be -nnn...)
 */
static int	nb_option_n(char **args)
{
	int	i;
	int	j;
	int	is_option_n;

	i = 0;
	is_option_n = 1;
	while (args[i] && is_option_n)
	{
		j = 0;
		if (args[i][j] == '-')
			j++;
		while (args[i][j] == 'n')
			j++;
		is_option_n = (args[i][j] == '\0');
		i++;
	}
	return (i - 1);
}

static int	write_print_on_error(char *str)
{
	if (str && write(STDOUT_FILENO, str, ft_strlen(str)) == -1)
	{
		ft_fprintf(STDERR_FILENO, "write: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	print_word(char **args, int i)
{
	if (!args[i])
		return (EXIT_SUCCESS);
	if (write_print_on_error(args[i]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (args[i + 1])
		if (write_print_on_error(" ") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @param args : expected to be : [-n[n...] [...]] [[...] NULL]
 */
int	ft_echo(char **args)
{
	int	i;
	int	is_n;

	if (!args)
		return (EXIT_FAILURE);
	if (!args[0])
		return (write_print_on_error("\n"));
	is_n = nb_option_n(args);
	i = is_n;
	while (args[i])
		if (print_word(args, i++) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (!is_n)
		if (write_print_on_error("\n") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
