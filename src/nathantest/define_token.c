/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:11:38 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/16 14:28:27 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nathantest.h"

int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	define_token(char *string)
{
	if (ft_strstr(string, "<<") == 1)
		return (HEREDOC);
	if (ft_strstr(string, ">") == 1 || ft_strstr(string, "<") == 1)
		return (OPERATOR);
	if (ft_strstr(string, "|") == 1)
		return (PIPE);
	if (ft_strstr(string, "-") == 1)
		return (FLAG);
    return(COMMAND);
}