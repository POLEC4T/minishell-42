/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:12:32 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/09 09:39:16 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_redirect_core(char *str, size_t i, size_t redir)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i = skip_redirection(str, i);
			i = skip_spaces(str, i);
			i = skip_word(str, i);
			redir++;
		}
		else if (ft_isblank(str[i]) == 0)
		{
			i = skip_word(str, i);
		}
		else
		{
			i++;
		}
	}
	return (redir);
}

size_t	count_args_core(char *str, size_t i, size_t args)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i = skip_redirection(str, i);
			i = skip_spaces(str, i);
			i = skip_word(str, i);
		}
		else if (str[i] && ft_isblank(str[i]) == 0)
		{
			i = skip_word(str, i);
			args++;
		}
		else
		{
			i++;
		}
	}
	return (args);
}

int	count_args(char *str)
{
	return ((int)count_args_core(str, 0, 0));
}

int	count_redirect(char *str)
{
	return ((int)count_redirect_core(str, 0, 0));
}
