/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:01 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 15:35:46 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;

	if (args && args[0])
	{
		ft_fprintf(STDERR_FILENO, "pwd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_fprintf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
