/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:55:25 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/16 16:21:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*elem_ptr;

	elem_ptr = malloc(sizeof(t_node));
	if (!elem_ptr)
		return (NULL);
	elem_ptr->content = content;
	elem_ptr->next = NULL;
	elem_ptr->prev = NULL;
	return (elem_ptr);
}
