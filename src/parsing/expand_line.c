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
	if (str[i] != '$' || str[i + 1] == ' ' || !str[i + 1])
		return (NULL);
	i++;
	while (str[i + len] != ' ' && str[i + len] != '\n' && str[i + len] && str[i
		+ len] != '\'' && str[i + len] != '\"')
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

static void	skip_redir_word(const char *str, size_t *i, size_t *len)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\n' && str[*i] != '"')
		(*i)++;
	while (str[*i])
	{
		(*len)++;
		(*i)++;
	}
}

static int	get_final_len(char *str, char *keyword, int type)
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
		if ((type == CMD && has_dollar_preceded_by_redir(str, i) != 1)
			|| type != CMD)
		{
			skip_redir_word(str, &i, &len);
			break ;
		}
		len++;
		i++;
	}
	if (keyword != NULL)
		len += ft_strlen(keyword);
	return (len);
}

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
			while (str[h] != ' ' && str[h] != '"' && str[h] != '\n' && str[h])
				h++;
			break ;
		}
		else
			h++;
	}
	return (h);
}
static char	*get_expanded_str(char *str, char *inter, int final_len, int type)
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
		if ((type == CMD && has_dollar_preceded_by_redir(str, i) != 1)
			|| type != CMD)
		{
			while (inter && inter[j])
			{
				expanded[i + j] = inter[j];
				j++;
			}
			while (str[h])
			{
				expanded[i + j] = str[h];
				j++;
				h++;
			}
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

// static char	*fill_expanded(char *str, char *inter, char *expanded, size_t i)
// {
// 	size_t	j;
// 	size_t	h;

// 	j = 0;
// 	h = find_end_inter(str, CMD);
// 	while (inter && inter[j])
// 	{
// 		expanded[i + j] = inter[j];
// 		j++;
// 	}
// 	while (str[h])
// 	{
// 		expanded[i + j] = str[h];
// 		j++;
// 		h++;
// 	}
// 	return (expanded);
// }

// static char	*get_expanded_str(char *str, char *inter, int final_len, int type)
// {
// 	char	*expanded;
// 	size_t	i;

// 	i = 0;
// 	expanded = ft_calloc(final_len + 1, sizeof(char));
// 	if (!expanded)
// 		return (NULL);
// 	while (str[i] && str[i] != '$')
// 	{
// 		expanded[i] = str[i];
// 		i++;
// 	}
// 	if ((type == CMD && has_dollar_preceded_by_redir(str, i) != 1)
// 		|| type != CMD)
// 		return (fill_expanded(str, inter, expanded, i));
// 	while (str[i])
// 	{
// 		expanded[i] = str[i];
// 		i++;
// 	}
// 	return (expanded);
// }

char	*expand_line(char *str, t_context *ctx, int type)
{
	char *keyword;
	char *expanded_word;
	char *expanded_str;
	size_t i;
	int in_single_quote;
	int in_double_quote;
	int expanded;

	if (str == NULL)
		return (str);
	if (ft_strchr(str, '$') == 0)
		return (str);

	expanded = 1;
	while (expanded)
	{
		expanded = 0;
		i = 0;
		in_single_quote = 0;
		in_double_quote = 0;
		while (str[i])
		{
			if (str[i] == '\'' && !in_double_quote)
			{
				in_single_quote = !in_single_quote;
				i++;
				continue ;
			}
			else if (str[i] == '"' && !in_single_quote)
			{
				in_double_quote = !in_double_quote;
				i++;
				continue ;
			}

			// Expansion si PAS dans quote simple
			if (!in_single_quote && str[i] == '$' && str[i + 1] != ' ' && str[i
				+ 1] != '\0')
			{
				if (type == CMD && has_dollar_preceded_by_redir(str, i) == 1
					&& count_dollar(str) == 1)
					return (str);
				else if (type == CMD && has_dollar_preceded_by_redir(str,
						i) == 1)
				{
					while (str[i] && str[i] != '$')
						i++;
				}
				else if (type != CMD)
				{
					while (str[i] && str[i] != '$')
						i++;
				}
				keyword = get_key_word(str + i);
				if (str[i + 1] == '?')
					expanded_word = ft_itoa(ctx->exit_code);
				else
					expanded_word = ft_get_env_val(ctx, keyword);
				expanded_str = get_expanded_str(str, expanded_word,
						get_final_len(str, expanded_word, type), type);
				free(keyword);
				free(expanded_word);
				free(str);
				str = expanded_str;
				expanded = 1;
				break ; // recommencer avec la nouvelle chaîne
			}
			i++;
		}
	}
	return (str);
}