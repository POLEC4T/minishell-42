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

// Cette fonction s’occupe uniquement de la récupération du mot-clé à expand
static size_t	find_expand_index(char *str, int *in_single, int *in_double)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		update_quotes(str[i], in_single, in_double);
		if (should_expand(str, i, *in_single))
			break ;
		i++;
	}
	return (i);
}

static char	*expand_word(char *str, size_t i, t_context *ctx, int type)
{
	char	*keyword;
	char	*expanded_word;
	char	*expanded_str;

	keyword = get_key_word(str + i);
	if (str[i + 1] == '?')
		expanded_word = ft_itoa(ctx->exit_code);
	else
		expanded_word = ft_get_env_val(ctx, keyword);
	expanded_str = get_expanded_str(str, expanded_word, get_final_len(str,
				expanded_word, type), type);
	free(keyword);
	free(expanded_word);
	free(str);
	return (expanded_str);
}

static int	handle_redir_case(char *str, size_t *i, int type)
{
	if (type == CMD && has_dollar_preceded_by_redir(str, *i) == 1)
	{
		if (count_dollars(str) == 1)
			return (1);
		(*i)++;
		while (str[*i] && str[*i] != '$')
			(*i)++;
	}
	else if (type != CMD)
	{
		while (str[*i] && str[*i] != '$')
			(*i)++;
	}
	return (0);
}

static char	*expand_one(char *str, t_context *ctx, int type, int *expanded)
{
	int		in_single;
	int		in_double;
	size_t	i;

	in_single = 0;
	in_double = 0;
	i = find_expand_index(str, &in_single, &in_double);
	if (!str[i])
		return (str);
	if (handle_redir_case(str, &i, type))
		return (str);
	*expanded = 1;
	return (expand_word(str, i, ctx, type));
}

char	*expand_line(char *str, t_context *ctx, int type)
{
	int	expanded;

	if (str == NULL)
		return (str);
	if (ft_strchr(str, '$') == 0)
		return (str);
	expanded = 1;
	while (expanded)
	{
		expanded = 0;
		str = expand_one(str, ctx, type, &expanded);
	}
	return (str);
}
