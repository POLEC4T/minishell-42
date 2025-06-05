/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:30 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 16:05:01 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end_inter(char *str, int type)
{
	int	h;

	h = 0;
	while (1)
	{
		while (str[h] != '$')
			h++;
		if ((type == CMD && has_dollar_preceded_by_redir(str, h) != 1)
			|| type != CMD)
		{
			h++;
			while (str[h] == ' ')
				h++;
			while (str[h] && (ft_isalnum(str[h]) == 1 || str[h] == '_'
					|| str[h] == '?'))
				h++;
			break ;
		}
		else
			h++;
	}
	return (h);
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
	while (1)
	{
		while (str[i] != '$')
		{
			expanded[i] = str[i];
			i++;
		}
		if ((type == CMD && !has_dollar_preceded_by_redir(str, i))
			|| type != CMD)
		{
			while (inter && inter[j])
			{
				expanded[i + j] = inter[j];
				j++;
			}
			while (str[h])
				expanded[i + j++] = str[h++];
			break ;
		}
		else
		{
			expanded[i] = str[i];
			i++;
		}
	}
	return (expanded);
}

void	update_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

int	should_expand(char *str, size_t i, int in_single)
{
	return (!in_single && str[i] == '$' && str[i + 1] != ' ' && str[i
			+ 1] != '\0');
}
