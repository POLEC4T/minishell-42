/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:30 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 15:12:10 by mniemaz          ###   ########.fr       */
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
			if (str[h] == '?')
				return (h++);
			while (ft_isblank(str[h]) == 1)
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
