/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:24:50 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 18:47:27 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * returns NULL and frees the pointers passed as arguments.
 */
void	*return_free(void *to_free1, void *to_free2, void *to_free3)
{
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	if (to_free3)
		free(to_free3);
	return (NULL);
}
