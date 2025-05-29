/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:58:01 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/29 10:38:19 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key_word(char *str)
{
	size_t	i;
	size_t	len;
	char	*key_word;

	len = 0;
	i = 0;
	if (str[i] != '$' || str[i + 1] == ' ')
		return (NULL);
	i++;
	while (str[i + len] != ' ' && str[i + len] != '\n' && str[i + len])
		len++;
	key_word = ft_calloc(len + 1, 1);
	len = 0;
	while (str[i + len] != ' ' && str[i + len] != '\n' && str[i + len] && str[i
		+ len] != '\'' && str[i + len] != '\"')
	{
		key_word[len] = str[i + len];
		len++;
	}
	key_word[len] = '\0';
	return (key_word);
}

static int	get_final_len(char *str, char *keyword)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (1)
	{
		while (str[i] && str[i] != '$')
		{
			i++;
			len++;
		}
		if (has_dollar_preceded_by_redir(str, i) != 1)
		{
			while (str[i] && str[i] != ' ' && str[i] != '\n')
				i++;
			while (str[i])
			{
				len++;
				i++;
			}
			break ;
		}
		else
		{
			len++;
			i++;
		}
	}
	if (keyword != NULL)
		len += ft_strlen(keyword);
	return (len);
}

static int	find_end_inter(char *str)
{
	int	h;

	h = 0;
	while (1)
	{
		while (str[h] != '$')
			h++;
		if (has_dollar_preceded_by_redir(str, h) != 1)
		{
			h++;
			while (str[h] == ' ')
				h++;
			while (str[h] != ' ' && str[h] != '\n' && str[h])
				h++;
			break ;
		}
		else
			h++;
	}
	return (h);
}

static char	*get_expanded_str(char *str, char *inter, int final_len)
{
	char	*expanded;
	size_t	i;
	size_t	j;
	size_t	h;

	i = 0;
	j = 0;
	h = find_end_inter(str);
	expanded = ft_calloc(final_len + 1, sizeof(char));
	while (1)
	{
		while (str[i] != '$')
		{
			expanded[i] = str[i];
			i++;
		}
		if (has_dollar_preceded_by_redir(str, i) != 1)
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

/**
 * Expands the line by replacing environment variables, one word by one word
 */
char	*expand_line(char *str, t_context *ctx, int type)
{
	size_t	i;
	char	*keyword;
	char	*expanded_word;
	char	*expanded_str;

	if (str == NULL)
		return (str);
	i = 0;
	if (ft_strchr(str, '$') == 0)
		return (str);
	while (str[i] != '$')
		i++;
	while (1)
	{
		if (type == CMD && has_dollar_preceded_by_redir(str, i) == 1
			&& count_dollar(str) == 1)
			return (str);
		else if (has_dollar_preceded_by_redir(str, i) == 1)
		{
			i++;
			while (str[i] && str[i] != '$')
				i++;
		}
		else
			break ;
	}
	keyword = get_key_word(str + i);
	if (str[i + 1] == '?')
	{
		expanded_word = ft_itoa(ctx->exit_code);
	}
	else
		expanded_word = ft_get_env_val(ctx, keyword);
	expanded_str = get_expanded_str(str, expanded_word, get_final_len(str,
				expanded_word));
	free(keyword);
	free(expanded_word);
	free(str);
	return (expand_line(expanded_str, ctx, type));
}
