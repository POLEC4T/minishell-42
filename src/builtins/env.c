/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:07 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/22 14:06:40 by mniemaz          ###   ########.fr       */
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
		if (env && env->key)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
		}
		if (env && env->value && env->value[0])
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}