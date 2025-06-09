/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line_utils_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:02:26 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/09 15:11:34 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_word(char *str)
{
	size_t	i;
	size_t	len;
	char	*key_word;

	len = 0;
	i = 0;
	if (!str[i + 1] || str[i] != '$' || ft_isblank(str[i + 1]))
		return (NULL);
	i++;
	while (ft_isalnum(str[i + len]) == 1 || str[i + len] == '_' || str[i
			+ len] == '?')
		len++;
	key_word = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (ft_isalnum(str[i + len]) == 1 || str[i + len] == '_' || str[i
			+ len] == '?')
	{
		key_word[len] = str[i + len];
		len++;
	}
	key_word[len] = '\0';
	return (key_word);
}

void	skip_redir_word(const char *str, size_t *i, size_t *len)
{
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_' || str[*i] == '?')
		(*i)++;
	while (str[*i])
	{
		(*len)++;
		(*i)++;
	}
}

int	get_final_len(char *str, char *keyword, int type)
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

int	has_dollar_preceded_by_redir(char *str, int i)
{
	int	j;

	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (0);
	j = i - 1;
	while (j >= 0 && (str[j] == '\\' || str[j] == ';' || ft_isblank(str[j])
			|| str[j] == '\'' || str[j] == '"'))
		j--;
	if (j >= 1 && str[j] == '<' && str[j - 1] == '<')
		return (1);
	return (0);
}

int	count_dollars(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
