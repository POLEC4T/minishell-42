/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <nle-gued@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:57:51 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 03:57:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*skip_leading_spaces(const char *ptr)
{
	while (*ptr && ft_isspace((unsigned char)*ptr))
		ptr++;
	return (ptr);
}

void	update_quote(const char c, char *quote)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote && c == *quote)
		*quote = 0;
}

const char	*find_pipe(const char *ptr, char *quote)
{
	while (*ptr)
	{
		update_quote(*ptr, quote);
		if (!*quote && *ptr == '|')
			break ;
		ptr++;
	}
	return (ptr);
}

const char	*skip_trailing_spaces(const char *start, const char *end)
{
	while (end >= start && ft_isspace((unsigned char)*end))
		end--;
	return (end);
}

int	is_segment_empty(const char *start, const char *end)
{
	return (end < start);
}
