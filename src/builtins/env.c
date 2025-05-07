/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:07 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/07 17:38:55 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief (builtin env) prints the environment variables
 */
void	ft_env(t_node **head)
{
	t_node		*tmp;
	t_key_value	*env;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		env = cast_to_key_value(tmp->content);
		if (env && env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		tmp = tmp->next;
	}
}
