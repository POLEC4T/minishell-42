/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <nle-gued@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:47:57 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 02:47:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_inter(char *expanded, char *inter, size_t i, size_t *j)
{
	size_t	k;

	k = 0;
	if (!inter)
		return ;
	while (inter[k])
	{
		expanded[i + k] = inter[k];
		k++;
	}
	*j = k;
}

void	copy_rest(char *expanded, char *str, size_t *j, size_t *h)
{
	while (str[*h])
		expanded[*j] = str[(*h)++];
}

char	*get_expanded_str(char *str, char *inter, int final_len, int type)
{
	char	*expanded;
	size_t	i;
	size_t	j;
	size_t	h;

	i = 0;
	j = 0;
	h = find_end_inter(str, type);
	expanded = ft_calloc(final_len + 1, sizeof(char));
	while (str[i] != '$')
	{
		expanded[i] = str[i];
		i++;
	}
	if ((type == CMD && !has_dollar_preceded_by_redir(str, i)) || type != CMD)
	{
		copy_inter(expanded, inter, i, &j);
		copy_rest(expanded, str, &j, &h);
	}
	else
	{
		expanded[i] = str[i];
		i++;
	}
	return (expanded);
}
