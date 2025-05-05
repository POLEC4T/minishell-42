/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:01 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/02 17:03:46 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **args)
{
    char *pwd;
    
	if (args && args[0])
	{
		ft_fprintf(STDERR_FILENO, "pwd: too many arguments\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_fprintf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		return ;
	}
	ft_fprintf(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
}