/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:30:43 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/14 14:54:16 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key_value	*cast_to_key_value(void *to_cast)
{
	if (!to_cast)
		return (NULL);
	return ((t_key_value *)to_cast);
}

t_token	*cast_to_token(void *to_cast)
{
	if (!to_cast)
		return (NULL);
	return ((t_token *)to_cast);
}

t_cmd	*cast_to_cmd(void *to_cast)
{
	if (!to_cast)
		return (NULL);
	return ((t_cmd *)to_cast);
}
