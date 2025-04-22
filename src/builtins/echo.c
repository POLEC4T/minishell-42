/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:48:01 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/22 15:15:51 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

static void	print_word(char **args, int i)
{
	ft_putstr_fd(args[i], STDOUT_FILENO);
	if (args[i + 1])
		ft_putstr_fd(" ", STDOUT_FILENO);
}

/**
 * @param args : expected to be : [-n] [[...] NULL]
 */
void	ft_echo(t_context *context, char **args)
{
	int	i;
	int	is_n;

    // TODO remove context if not needed
    // (i think i will need it in the future for exit code)
	(void)context; 
	if (!args)
		return ;
	if (!args[0])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	is_n = is_option_n(args[0]);
	i = is_n;
	while (args[i])
	{
		print_word(args, i);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
