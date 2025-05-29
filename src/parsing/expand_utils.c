/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:42:09 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/29 18:50:30 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_dollar_preceded_by_redir(char *str, int i)
{
	int	j;

	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (0);
	j = i - 1;
	while (j >= 0 && (str[j] == '\\' || str[j] == ';' || str[j] == ' '
			|| str[j] == '\'' || str[j] == '"'))
		j--;
	if (j >= 1 && str[j] == '<' && str[j - 1] == '<')
		return (1);
	return (0);
}

// Compte le nombre de '$' en dehors des quotes simples
int	count_dollar(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
	}
	return (count);
}
