/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:07 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 16:31:25 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief (builtin env) prints the environment variables
 */
int	ft_env(t_node **head)
{
	t_node		*tmp;
	t_key_value	*env;

	if (!head)
		return (EXIT_SUCCESS);
	tmp = *head;
	while (tmp)
	{
		env = cast_to_key_value(tmp->content);
		if (env && env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
