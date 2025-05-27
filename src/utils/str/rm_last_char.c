/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_last_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:24:31 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/27 15:26:15 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief removes the last character of the string
 * @details made to remove the '\n' character at the end of the ret of gnl
 */
char	*rm_last_char(char *str)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str_len > 0)
		str[str_len - 1] = '\0';
	return (str);
}
