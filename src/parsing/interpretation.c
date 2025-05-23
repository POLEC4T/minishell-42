/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:58:01 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/16 13:33:44 by mniemaz          ###   ########.fr       */
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
	if (str[i] != '$' || str[i + 1] == ' ')
		return (NULL);
	i++;
	while (str[i + len] != ' ' && str[i + len])
		len++;
	key_word = ft_calloc(len + 1, 1);
	len = 0;
	while (str[i + len] != ' ' && str[i + len])
	{
		key_word[len] = str[i + len];
		len++;
	}
	key_word[len] = '\0';
	return (key_word);
}

int	interlen(char *str, char *keyword)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		len++;
	}
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i])
	{
		len++;
		i++;
	}
	if (keyword != NULL)
		len += ft_strlen(keyword);
	return (len);
}

int	find_end_inter(char *str)
{
	int	h;

	h = 0;
	while (str[h] != '$')
		h++;
	h++;
	while (str[h] == ' ')
		h++;
	while (str[h] != ' ' && str[h])
		h++;
	return (h);
}

char	*replace(char *str, char *inter, int interlen)
{
	char	*replace;
	size_t	i;
	size_t	j;
	size_t	h;

	i = -1;
	j = 0;
	h = 0;
	h = find_end_inter(str);
	replace = ft_calloc(interlen + 1, 1);
	while (str[++i] != '$')
		replace[i] = str[i];
	if (inter)
		while (inter[j])
		{
			replace[i + j] = inter[j];
			j++;
		}
	while (str[h])
	{
		replace[i + j] = str[h];
		j++;
		h++;
	}
	return (replace);
}

char	*interpretation(char *str, t_context *ctx)
{
	size_t	i;
	char	*keyword;
	char	*inter;
	int		len;
	char	*repl;

	i = 0;
	if (ft_strchr(str, '$') == 0)
		return (str);
	while (str[i] != '$')
		i++;
	keyword = get_key_word(str + i);
	if (str[i + 1] == '?')
		inter = ft_itoa(ctx->exit_code);
	else
		inter = ft_get_env_val(ctx, keyword);
	len = interlen(str, inter);
	repl = replace(str, inter, len);
	free(keyword);
	free(inter);
	free(str);
	return (interpretation(repl, ctx)); 
}
